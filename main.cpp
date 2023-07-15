#include <bits/stdc++.h>
#include <windows.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#define pdd pair<double,double>


// by Dr Arasteh
// by Dr Vosoghi Vahdat
// by MohammadAmin Alamalhoda  ma.alamalhoda@gmail.com


using namespace std;
//{ *struct for games*
struct board
{
    double x,y;
    double stpx;
    double h,w;
};
typedef struct ball
{
    double x,y;
    double stpx,stpy;
    double rad;
}ball;
struct brick
{
    double x,y;
    double h,w;
    int strength;
};
//}
//{ *struct for saving and loading data*
struct history
{
    int day,month,year;
    int hour,minute;
};
struct gameheadinf
{
    int codegame,score,live,level;
    ///option of
};
struct gamebodyinf
{
    bool player_2;
    vector <brick> setbrick;
    /// option information

    /// okay
};
//}
//{ *struct for menu*
struct button
{
    SDL_Rect rect,smallrect;
    void getdata(int x,int y,int w,int h)
    {
        rect.x=x;
        smallrect.x=x+1;
        rect.y=y;
        smallrect.y=y+1;
        rect.w=w;
        smallrect.w=w-2;
        rect.h=h;
        smallrect.h=h-2;
    }
};
struct list_button
{
    SDL_Rect page;
    vector <button> buttons;
    void getdata(int x,int y,int w,int h)
    {
        page.x=x,page.y=y,page.w=w,page.h=h;
    }
};
//}

//{ *general information*
int W,H;//size of window
ball toop;
board t1;
vector <brick> ajor;
int num_of_brick=14;
int hmax;
int max_w;
int level=1,Lives=3;
int damage=level;
int scores=0;
int w0=20,h0=20;
int newplayer=0;
int newgame=0;
int createcodegame=1;
int difficulty=0; /**   1:easy
                        2:normal
                        3:hard
                        **/
int theme_ball;
int theme_board;
int theme_control;

//Mix_Chunk *chik;
//Mix_Chunk *bomb_sound;
//Mix_Chunk *live_sound;

SDL_Texture *digit[3][10];
SDL_Texture *alfabet[26];

SDL_Texture *optionmenu_page[3];
SDL_Texture *startmenu_background[3];

SDL_Texture *maingame_background[3];
SDL_Texture *maingame_brick[3];
SDL_Texture *maingame_ball[4];
SDL_Texture *maingame_board[4];
SDL_Texture *maingame_live[3];
SDL_Texture *maingame_score[3];
SDL_Texture *maingame_level[3];
SDL_Texture *maingame_damage[3];

SDL_Texture *stopmenu_page[3];
SDL_Texture *stopmenu_button_resume[3][2];
SDL_Texture *stopmenu_button_option[3][2];
SDL_Texture *stopmenu_button_savegame[3][2];
SDL_Texture *stopmenu_button_loadgame[3][2];
SDL_Texture *stopmenu_button_playermenu[3][2];
//high
SDL_Texture *mainmenu_background[3];
SDL_Texture *mainmenu_page[3];
SDL_Texture *mainmenu_title[3];
SDL_Texture *mainmenu_button_start[3][2];
SDL_Texture *mainmenu_button_highscore[3][2];
SDL_Texture *mainmenu_button_option[3][2];
SDL_Texture *mainmenu_button_help[3][2];
SDL_Texture *mainmenu_button_credit[3][2];
SDL_Texture *mainmenu_button_exit[3][2];

SDL_Texture *playmenu_page[3];
SDL_Texture *playmenu_title[3];
SDL_Texture *playmenu_button_newgame[3][2];
SDL_Texture *playmenu_button_loadgame[3][2];
SDL_Texture *playmenu_button_mainmenu[3][2];
SDL_Texture *playmenu_button_option[3][2];



//}

//{ *information of current player*
string name_current_player;
int current_codegame;
//}
//{ *information of current game*
int numofgame;
gamebodyinf informaion_of_currentgame;
//}

//{all_function
    int mainmenu(SDL_Renderer *renderer);
    void drawframe(SDL_Renderer* renderer);
    bool select_button(button c,POINT b);
    void drawdigi(SDL_Renderer * renderer,int num,int y);
    int optionmenu(SDL_Renderer * renderer);
    int savegame(SDL_Renderer *renderer);
    int loadgamemenu(SDL_Renderer * renderer);
    int stopmenu(SDL_Renderer * renderer);
    int playmenu(SDL_Renderer * renderer);
    bool checkname(string name);
    int startmenu(SDL_Renderer *renderer);
    int maingame_01player(SDL_Renderer* renderer);
    int highscoremenu(SDL_Renderer * renderer);
    string int_to_string(int n);
//}


//{ *menus*


bool select_button(button c,POINT b)
{
    SDL_Rect a=c.rect;
    if(b.x>=a.x && b.y>=a.y && b.y<=a.y+a.h && b.x<=a.x+a.w)
        return 1;
    return 0;
}
int optionmenu(SDL_Renderer * renderer)
{
    SDL_Rect sizerect;
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    POINT mouse;
    sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    button theme_ball_button[4];
    button theme_board_button[4];
    button theme_control_button[2];

    theme_board_button[0].getdata(609,301,16,17);
    theme_board_button[1].getdata(826,303,16,17);
    theme_board_button[2].getdata(611,249,16,17);
    theme_board_button[3].getdata(826,249,16,17);
//
    theme_ball_button[0].getdata(553,397,16,17);
    theme_ball_button[1].getdata(636,397,16,17);
    theme_ball_button[2].getdata(717,400,16,17);
    theme_ball_button[3].getdata(786,400,16,17);

    theme_control_button[0].getdata(587,483,16,17);
    theme_control_button[1].getdata(754,482,16,17);

    bool let_return=0;

    while(true)
    {
        GetCursorPos(&mouse);
        SDL_PumpEvents();
        sizerect.x=W/2-225,sizerect.y=150,sizerect.w=450,sizerect.h=420;
        SDL_RenderCopy(renderer,optionmenu_page[0],NULL,&sizerect);
        if(state[SDL_SCANCODE_ESCAPE] && let_return)
        {
            sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
            SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
            return 0;
        }
        else if(!state[SDL_SCANCODE_ESCAPE])
            let_return=1;

        if(theme_board==0)
            boxRGBA(renderer,612,304,624,317,46,250,240,255);
        if(theme_board==1)
            boxRGBA(renderer,827,304,839,317,46,250,240,255);
        if(theme_board==2)
            boxRGBA(renderer,612,250,624,263,46,250,240,255);
        if(theme_board==3)
            boxRGBA(renderer,827,250,839,263,46,250,240,255);
        for(int i=0;i<4;i++)
            if(select_button(theme_board_button[i],mouse) && (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                theme_board=i;

        if(theme_ball==0)
            boxRGBA(renderer,555,400,567,413,46,250,240,255);
        if(theme_ball==1)
            boxRGBA(renderer,638,400,650,413,46,250,240,255);
        if(theme_ball==2)
            boxRGBA(renderer,718,401,729,414,46,250,240,255);
        if(theme_ball==3)
            boxRGBA(renderer,787,401,799,414,46,250,240,255);
        for(int i=0;i<4;i++)
            if(select_button(theme_ball_button[i],mouse) && (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                theme_ball=i;

        if(theme_control==0)
            boxRGBA(renderer,589,485,601,498,46,250,240,255);
        if(theme_control==1)
            boxRGBA(renderer,756,484,768,497,46,250,240,255);
        for(int i=0;i<2;i++)
            if(select_button(theme_control_button[i],mouse) && (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                theme_control=i;
        SDL_RenderPresent(renderer);
    }
    fstream theme;
    theme.open("theme.txt",ios::out | ios::trunc);
    theme<<createcodegame<<" "<<theme_ball<<" "<<theme_board<<" "<<theme_control<<" ";
    theme.close();
}
int savegame(SDL_Renderer *renderer)
{
    string address="codegame/";
    address+=int_to_string(current_codegame);
    address+=".txt";
    fstream codegame;
    codegame.open(address.c_str(),ios::out | ios::trunc);
    codegame<<Lives<<" "<<level<<" "<<scores<<" "<<damage<<" "<<difficulty<<" "<<ajor.size()<<" ";
    for(int i=0;i<ajor.size();i++)
        codegame<<ajor[i].x<<" "<<ajor[i].y<<" "<<ajor[i].strength<<" ";
    codegame.close();
    return 1;
}
void printstring(SDL_Renderer *renderer,string s,int x,int y)
{
    int mark=x;
    SDL_Rect sizerect;
    for(int i=0;i<s.size();i++)
    {
        if((s[i]>=97 && s[i]<=122) || (s[i]>=65 && s[i]<=80))
        {
            sizerect.x=mark,sizerect.y=y,sizerect.w=15,sizerect.h=30;
            SDL_RenderCopy(renderer,alfabet[int(tolower(s[i])-'a')],NULL,&sizerect);
        }
        if(s[i]>=48 && s[i]<=57)
        {
            sizerect.x=mark,sizerect.y=y,sizerect.w=15,sizerect.h=30;
            SDL_RenderCopy(renderer,digit[0][int(s[i]-'0')],NULL,&sizerect);
        }
        mark+=16;
    }
}
string int_to_string(int n)
{
    if(n==0)
        return "0";
    string ans;
    int m=0,num=0;
    while(n)
    {
        m*=10;
        m+=n%10;
        n/=10;
        num++;
    }
    while(num)
    {
        ans+='0'+m%10;
        m/=10;
        num--;
    }
    return ans;
}
int loadgamemenu(SDL_Renderer * renderer)
{
    string address_player_codegame="player_codegame/";
    address_player_codegame+=name_current_player;
    address_player_codegame+=".txt";
    fstream player_codegame;
    fstream codegame;
    player_codegame.open(address_player_codegame.c_str());
    vector <gameheadinf> v;
    string s;
    int code;
    while(player_codegame.good())
    {
        player_codegame>>code;
        s="codegame/";
        s+=int_to_string(code);
        s+=".txt";
        codegame.open(s.c_str());
        if(codegame.good())
        {
            gameheadinf a;
            codegame>>a.live>>a.level>>a.score;
            a.codegame=code;
            v.push_back(a);
        }
        codegame.close();
    }
    player_codegame.close();
    SDL_Rect sizerect;
    sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    int num_of_load=v.size()-1;
    for(int i=0;i<min(num_of_load,5);i++)
    {
        boxRGBA(renderer,150-1,150+i*80-1,W-150+1,150+i*80+60+1,46,250,240,255);
        boxRGBA(renderer,150,150+i*80,W-150,150+i*80+60,0,0,0,255);
        string codegame,score,live,level;
        codegame=int_to_string(v[i].codegame);
        score=int_to_string(v[i].score);
        live=int_to_string(v[i].live);
        level=int_to_string(v[i].level);
        string text=" codegame ";
        text+=codegame,text+=" score ",text+=score,text+=" level ",text+=level,text+=" live ",text+=live;
        printstring(renderer,text,150+5,150+i*80+15);
    }
    SDL_RenderPresent(renderer);
    button loadmenu_button[min(num_of_load,5)];
    bool let_click=0;
    for(int i=0;i<min(num_of_load,5);i++)
        loadmenu_button[i].getdata(150-1,150+i*80-1,W-300+2,60);
    SetCursorPos(W/2,50);
    POINT mouse;
    while(true)
    {
        GetCursorPos(&mouse);
        SDL_PumpEvents();
        for(int i=0;i<min(num_of_load,5);i++)
        {
            if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && select_button(loadmenu_button[i],mouse))
            {
                    current_codegame=v[i].codegame;
                    return 0;
            }
        }

    }
}
int stopmenu(SDL_Renderer * renderer)
{
    //ShowCursor(true);
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    bool let_return=0;
    int command;
    boxRGBA(renderer,0,0,W,H,0,0,0,160);
    POINT mouse;
    SDL_Rect sizerect;
    button stopmenu_button[4];
    for(int i=0;i<4;i++)
        stopmenu_button[i].getdata(W/2-150,230+i*60,250,50);
    fstream player_codegame;
    string address="player_codegame/";
    address+=name_current_player;
    address+=".txt";
    player_codegame.open(address.c_str());
    while(true)
    {
        //ShowCursor(true);
        command=0;
        SDL_PumpEvents();
        sizerect.x=W/2-200,sizerect.y=200,sizerect.w=350,sizerect.h=320;
        SDL_RenderCopy(renderer,stopmenu_page[0],NULL,&sizerect);
        GetCursorPos(&mouse);
        if(select_button(stopmenu_button[0],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,stopmenu_button_resume[0][1],NULL,&(stopmenu_button[0].smallrect)),command=1;
            else
                SDL_RenderCopy(renderer,stopmenu_button_resume[0][1],NULL,&(stopmenu_button[0].rect));
        }
        else
            SDL_RenderCopy(renderer,stopmenu_button_resume[0][0],NULL,&(stopmenu_button[0].rect));
        if(select_button(stopmenu_button[1],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,stopmenu_button_option[0][1],NULL,&(stopmenu_button[1].smallrect)),command=2;
            else
                SDL_RenderCopy(renderer,stopmenu_button_option[0][1],NULL,&(stopmenu_button[1].rect));
        }
        else
            SDL_RenderCopy(renderer,stopmenu_button_option[0][0],NULL,&(stopmenu_button[1].rect));
        if(select_button(stopmenu_button[2],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,stopmenu_button_savegame[0][1],NULL,&(stopmenu_button[2].smallrect)),command=3;
            else
                SDL_RenderCopy(renderer,stopmenu_button_savegame[0][1],NULL,&(stopmenu_button[2].rect));
        }
        else
            SDL_RenderCopy(renderer,stopmenu_button_savegame[0][0],NULL,&(stopmenu_button[2].rect));

        if(select_button(stopmenu_button[3],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,stopmenu_button_playermenu[0][1],NULL,&(stopmenu_button[3].smallrect)),command=4;
            else
                SDL_RenderCopy(renderer,stopmenu_button_playermenu[0][1],NULL,&(stopmenu_button[3].rect));
        }
        else
            SDL_RenderCopy(renderer,stopmenu_button_playermenu[0][0],NULL,&(stopmenu_button[3].rect));

        //SDL_RenderPresent(renderer);
        if(!state[SDL_SCANCODE_ESCAPE] && let_return==0)
            let_return=1;

        if(state[SDL_SCANCODE_ESCAPE])
            if(let_return)
            {
                //ShowCursor(false);
                return 0;
            }
        if(command==1)
        {
            //ShowCursor(false);
            return 0;
        }
        if(command==2)
            optionmenu(renderer);
        if(command==3)
        {
            savegame(renderer);
            return 0;
        }
        if(command==4)
        {
            player_codegame.close();
            sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
            SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
            return 1;
        }
        SDL_RenderPresent(renderer);
    }
}
bool let_key[32];
bool let_num[10];
bool checkname(string name)
{
    fstream fname;
    fname.open("fname.txt");
    string a;
    while(fname.good())
    {
        fname>>a;
        if(a==name)
        {
            fname.close();
            return 1;
        }

    }
    fname.close();
    return 0;
}
int startmenu(SDL_Renderer *renderer)
{
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    SDL_Rect sizerect;
    bool  change=1;
    stack <char> text_L;
    stack <char> text_R;
    fstream fname;
    while(true)
    {
        SDL_PumpEvents();
        for(int i=4;i<=29;i++)
        {
            if(state[i] && let_key[i-4] && (text_L.size()+text_R.size()<20))
                text_L.push('a'+i-4),let_key[i-4]=0;
            else if(!state[i])
                let_key[i-4]=1;
        }
        for(int i=30;i<=38;i++)
        {
            if(state[i] && let_num[i-29] && (text_L.size()+text_R.size()<20))
                text_L.push('0'+i-29),let_num[i-29]=0;
            else if(!state[i])
                let_num[i-29]=1;
        }
        if(state[39] && let_num[0] && (text_L.size()+text_R.size()<20))
            text_L.push('0'),let_num[0]=0;
        else if(!state[39])
            let_num[0]=1;
//    SDL_SCANCODE_RETURN = 40,
//    SDL_SCANCODE_ESCAPE = 41,
//    SDL_SCANCODE_BACKSPACE = 42,
//    SDL_SCANCODE_TAB = 43,
//    SDL_SCANCODE_SPACE = 44,
        if(state[SDL_SCANCODE_LEFT] && let_key[30])
            text_R.push(text_L.top()),text_L.pop(),let_key[30]=0;
        else if(!state[SDL_SCANCODE_LEFT])
            let_key[30]=1;

        if(state[SDL_SCANCODE_RIGHT] && let_key[31])
            text_L.push(text_R.top()),text_R.pop(),let_key[31]=0;
        else if(!state[SDL_SCANCODE_RIGHT])
            let_key[31]=1;

        if(state[SDL_SCANCODE_BACKSPACE] && let_key[28] && text_L.size()!=0)
            text_L.pop(),let_key[28]=0;
        else if(!state[SDL_SCANCODE_BACKSPACE])
            let_key[28]=1;

        if(state[SDL_SCANCODE_SPACE] && let_key[29])
            text_L.push(' '),let_key[29]=0;
        else if(!state[SDL_SCANCODE_SPACE])
            let_key[29]=0;

        if(state[SDL_SCANCODE_ESCAPE] && let_key[27])
        {
            let_key[27]=0;
            sizerect.x=0,sizerect.y=0,sizerect.h=H,sizerect.w=W;
            SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
            return 0;
        }
        else if(!state[SDL_SCANCODE_ESCAPE])
            let_key[27]=1;

        if(state[SDL_SCANCODE_RETURN] && let_key[26])
        {
            let_key[26]=0;
            stack <char> k;
            while(text_L.size())
                k.push(text_L.top()),text_L.pop();
            string name;
            while(k.size())
                name+=k.top(),k.pop();
            while(text_R.size())
                name+=text_R.top(),text_R.pop();
            if(checkname(name))
            {
                name_current_player=name;
                return 0;
            }
            else
            {
                textRGBA(renderer,W/2-240,H/2+45,"are you a new player ?",1,30,46,254,240,255);
                button yes,no;
                int command=0;
                SDL_Texture *a,*b;

                SDL_SetRenderTarget(renderer,a);
                textRGBA(renderer,W/2+160,H/2+45,"no",1,30,46,254,240,255);
                SDL_SetRenderTarget(renderer,NULL);
                yes.getdata(W/2+150-70-1,H/2+40-1,50,30);
                no.getdata(W/2+150-1,H/2+40-1,50,30);
                POINT mouse;
                    while(true)
                    {
                        command=0;
                        SDL_PumpEvents();
                        GetCursorPos(&mouse);
                        if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && select_button(yes,mouse))
                        {
                            boxRGBA(renderer,W/2+150-70,H/2+40,W/2+200-70,H/2+70,46,254,240,255);
                            boxRGBA(renderer,W/2+150-70+1,H/2+40+1,W/2+200-70-1,H/2+70-1,0,0,0,255);
                            textRGBA(renderer,W/2+160-74,H/2+45,"yes",1,30,46,254,240,255);
                            command=1;
                        }
                        else
                        {
                            boxRGBA(renderer,W/2+150-70-1,H/2+40-1,W/2+200-70+1,H/2+70+1,46,254,240,255);
                            boxRGBA(renderer,W/2+150-70,H/2+40,W/2+200-70,H/2+70,0,0,0,255);
                            textRGBA(renderer,W/2+160-74,H/2+45,"yes",1,30,46,254,240,255);
                        }
                        if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && select_button(no,mouse))
                        {
                            boxRGBA(renderer,W/2+150,H/2+40,W/2+200,H/2+70,46,254,240,255);
                            boxRGBA(renderer,W/2+150+1,H/2+40+1,W/2+200-1,H/2+70-1,0,0,0,255);
                            textRGBA(renderer,W/2+160,H/2+45,"no",1,30,46,254,240,255);
                            command=2;
                        }
                        else
                        {
                            boxRGBA(renderer,W/2+150-1,H/2+40-1,W/2+200+1,H/2+70+1,46,254,240,255);
                            boxRGBA(renderer,W/2+150,H/2+40,W/2+200,H/2+70,0,0,0,255);
                            textRGBA(renderer,W/2+160,H/2+45,"no",1,30,46,254,240,255);
                        }
                        SDL_RenderPresent(renderer);
                        SDL_Delay(40);
                        if(command==1)
                        {
                            fname.open("fname.txt",ios::app | ios::in | ios::out);
                            name_current_player=name;
                            fname<<name<<" ";
                            return 0;
                        }
                        if(command==2)
                            break;
                    }
                SDL_RenderPresent(renderer);
            }
        }
        else if(!state[SDL_SCANCODE_RETURN])
            let_key[26]=1;

        if(change)
        {
            stack <char> m=text_L,n=text_R,k;
            while(m.size())
                k.push(m.top()),m.pop();
            string name="ENTER NAME:";
            while(k.size())
                name+=k.top(),k.pop();
            while(n.size())
                name+=n.top(),n.pop();
            sizerect.x=0,sizerect.y=0,sizerect.h=H,sizerect.w=W;
            SDL_RenderCopy(renderer,startmenu_background[0],NULL,&sizerect);
            boxRGBA(renderer,W/2-250-1,H/2-5-1,W/2+200+1,H/2+30+1,46,254,240,255);
            boxRGBA(renderer,W/2-250,H/2-5,W/2+200,H/2+30,0,0,0,255);
            textRGBA(renderer,W/2-240,H/2,name.c_str(),1,30,46,254,240,255);
            SDL_RenderPresent(renderer);
        }
    }

}
int playmenu(SDL_Renderer *renderer)
{
//    ShowCursor(true);
    SDL_Rect sizerect;
    sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    bool let_return=0;
    int command;
    POINT mouse;
    button playmenu_button[4];
    for(int i=0;i<4;i++)
       playmenu_button[i].getdata(W/2-150,230+i*60,250,50);
    fstream player_codegame;
    bool let_return_mainmenu=0;
    bool let_loadgame=0;
    while(true)
    {
        command=0;
        SDL_PumpEvents();
        sizerect.x=W/2-200,sizerect.y=200,sizerect.w=350,sizerect.h=300;
        SDL_RenderCopy(renderer,playmenu_page[0],NULL,&sizerect);
        GetCursorPos(&mouse);
        string address="player_codegame/";
        address+=name_current_player;
        address+=".txt";
        player_codegame.open(address.c_str());
        while(player_codegame.good())
        {
            int c;
            player_codegame>>c;
            string addressp="codegame/"+int_to_string(c)+".txt";
            fstream codegame;
            codegame.open(addressp.c_str());
            if(codegame.good())
                let_loadgame=1;
            codegame.close();
        }
        player_codegame.close();
        if(select_button(playmenu_button[0],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,playmenu_button_newgame[0][1],NULL,&(playmenu_button[0].smallrect)),command=1;
            else
                SDL_RenderCopy(renderer,playmenu_button_newgame[0][1],NULL,&(playmenu_button[0].rect));
        }
        else
            SDL_RenderCopy(renderer,playmenu_button_newgame[0][0],NULL,&(playmenu_button[0].rect));
        if(select_button(playmenu_button[1],mouse) && let_loadgame)
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,playmenu_button_loadgame[0][1],NULL,&(playmenu_button[1].smallrect)),command=2;
            else
                SDL_RenderCopy(renderer,playmenu_button_loadgame[0][1],NULL,&(playmenu_button[1].rect));
        }
        else
            SDL_RenderCopy(renderer,playmenu_button_loadgame[0][0],NULL,&(playmenu_button[1].rect));
        if(select_button(playmenu_button[2],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,playmenu_button_option[0][1],NULL,&(playmenu_button[2].smallrect)),command=3;
            else
                SDL_RenderCopy(renderer,playmenu_button_option[0][1],NULL,&(playmenu_button[2].rect));
        }
        else
            SDL_RenderCopy(renderer,playmenu_button_option[0][0],NULL,&(playmenu_button[2].rect));

        if(select_button(playmenu_button[3],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_RenderCopy(renderer,playmenu_button_mainmenu[0][1],NULL,&(playmenu_button[3].smallrect));
                if(let_return_mainmenu==1)
                    command=4,let_return_mainmenu=0;
            }
            else
                SDL_RenderCopy(renderer,playmenu_button_mainmenu[0][1],NULL,&(playmenu_button[3].rect)),let_return_mainmenu=1;
        }
        else
            SDL_RenderCopy(renderer,playmenu_button_mainmenu[0][0],NULL,&(playmenu_button[3].rect)),let_return_mainmenu=1;
        SDL_RenderPresent(renderer);
        int c=0;
        if(command==1)
        {
            newgame=1;
            current_codegame=createcodegame;
            createcodegame++;
            fstream theme;
            theme.open("theme.txt",ios::out | ios::trunc);
            theme<<createcodegame<<" "<<theme_ball<<" "<<theme_board<<" "<<theme_control<<" ";
            theme.close();
            sizerect.x=0,sizerect.y=0,sizerect.h=H,sizerect.w=W;
            SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
            textRGBA(renderer,100,100,"choose a difficulty (1:easy 2:normal 3:hard)",1,30,46,250,240,255);
            SDL_RenderPresent(renderer);
            while(true)
            {
                SDL_PumpEvents();
                if(state[SDL_SCANCODE_1])
                {
                    difficulty=1;
                    break;
                }
                if(state[SDL_SCANCODE_2])
                {
                    difficulty=2;
                    break;
                }
                if(state[SDL_SCANCODE_3])
                {
                    difficulty=3;
                    break;
                }
            }
            c=maingame_01player(renderer);
            let_return_mainmenu=0;
        }
        if(command==2)
        {
            newgame=0;
            loadgamemenu(renderer);
            c=maingame_01player(renderer);
            let_return_mainmenu=0;
        }
        if(command==3)
            c=optionmenu(renderer);
        if(command==4)
            return 0;
        if(c)
            return c-1;
    }
}
int highscoremenu(SDL_Renderer * renderer)
{
    SDL_Rect sizerect;
    sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    fstream highscore;
    highscore.open("highscore.txt");
    string esm[5];
    int sc[5];
    for(int i=0;i<5;i++)
        highscore>>esm[i]>>sc[i];
    for(int i=0;i<5;i++)
        textRGBA(renderer,200,200+i*100,(int_to_string(i+1)+"."+esm[i]+"   "+int_to_string(sc[i])).c_str(),1,30,46,250,240,255);
    SDL_RenderPresent(renderer);
    bool let_return=0;
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    while(true)
    {
        SDL_PumpEvents();
        if(let_return && state[SDL_SCANCODE_ESCAPE])
           return 0;
        else if(!state[SDL_SCANCODE_ESCAPE])
            let_return=1;
    }

}
int mainmenu(SDL_Renderer *renderer)
{
    //ShowCursor(true);
    SDL_Rect sizerect;
    sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    bool let_return=0;
    int command;
    POINT mouse;
    bool let_exit=0;
    button mainmenu_button[4];
    for(int i=0;i<5;i++)
       mainmenu_button[i].getdata(W/2-150,230+i*60,250,50);
    while(true)
    {
        command=0;
        SDL_PumpEvents();
        sizerect.x=W/2-200,sizerect.y=180,sizerect.w=350,sizerect.h=350;
        SDL_RenderCopy(renderer,mainmenu_page[0],NULL,&sizerect);
        GetCursorPos(&mouse);
        if(select_button(mainmenu_button[0],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,mainmenu_button_start[0][1],NULL,&(mainmenu_button[0].smallrect)),command=1;
            else
                SDL_RenderCopy(renderer,mainmenu_button_start[0][1],NULL,&(mainmenu_button[0].rect));
        }
        else
            SDL_RenderCopy(renderer,mainmenu_button_start[0][0],NULL,&(mainmenu_button[0].rect));
        if(select_button(mainmenu_button[1],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,mainmenu_button_option[0][1],NULL,&(mainmenu_button[1].smallrect)),command=2;
            else
                SDL_RenderCopy(renderer,mainmenu_button_option[0][1],NULL,&(mainmenu_button[1].rect));
        }
        else
            SDL_RenderCopy(renderer,mainmenu_button_option[0][0],NULL,&(mainmenu_button[1].rect));
        if(select_button(mainmenu_button[2],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                SDL_RenderCopy(renderer,mainmenu_button_highscore[0][1],NULL,&(mainmenu_button[2].smallrect)),command=3;
            else
                SDL_RenderCopy(renderer,mainmenu_button_highscore[0][1],NULL,&(mainmenu_button[2].rect));
        }
        else
            SDL_RenderCopy(renderer,mainmenu_button_highscore[0][0],NULL,&(mainmenu_button[2].rect));
        if(select_button(mainmenu_button[3],mouse))
        {
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_RenderCopy(renderer,mainmenu_button_exit[0][1],NULL,&(mainmenu_button[3].smallrect));
                if(let_exit)
                    command=4,let_exit=0;
            }
            else
                SDL_RenderCopy(renderer,mainmenu_button_exit[0][1],NULL,&(mainmenu_button[3].rect)),let_exit=1;
        }
        else
            SDL_RenderCopy(renderer,mainmenu_button_exit[0][0],NULL,&(mainmenu_button[3].rect)),let_exit=1;
        SDL_RenderPresent(renderer);
        int c=0;
        if(command==1)
        {
            startmenu(renderer);
            c=playmenu(renderer);
            let_exit=0;
        }
        if(command==2)
            c=optionmenu(renderer);
        if(command==3)
            c=highscoremenu(renderer);
        if(command==4)
        {
            return 0;
        }
        if(c)
        {
            return c-1;
        }
    }
}
int losemenu(SDL_Renderer *renderer)
{

}
//}
//{ *maingame*

void drawdigi(SDL_Renderer *renderer,int num,int y)
{
    int w=40;
    SDL_Rect sizerect;
    if(num==0)
    {
        w+=10;
        sizerect.x=W-w,sizerect.y=y,sizerect.h=20,sizerect.w=10;
        SDL_RenderCopy(renderer,digit[0][0],NULL,&sizerect);
    }
    while(num)
    {
        w+=10;
        sizerect.x=W-w,sizerect.y=y,sizerect.h=20,sizerect.w=10;
        SDL_RenderCopy(renderer,digit[0][num%10],NULL,&sizerect);
        w+=6;
        num/=10;
    }
}
//void(string s);
//{
//    cin>>s;
//    ofstream kod("names.txt");
//
//}

void drawframe(SDL_Renderer *renderer)
{
    ///load background
    //int max_w=(W*2)/3;
//    SDL_SetRenderDrawColor(renderer,0,0,0,255);
//    SDL_RenderClear(renderer);
    SDL_Rect sizerect;

    sizerect.x=0,sizerect.y=0,sizerect.h=H,sizerect.w=W;
    SDL_RenderCopy(renderer,maingame_background[0],NULL,&sizerect);
    /// okay
    sizerect.x=t1.x,sizerect.y=t1.y,sizerect.w=t1.w,sizerect.h=t1.h;
    SDL_RenderCopy(renderer,maingame_board[theme_board],NULL,&sizerect);
//    filledCircleRGBA(renderer, toop.x,toop.y,toop.rad,0,255,255,255);
    sizerect.x=toop.x-toop.rad,sizerect.y=toop.y-toop.rad,sizerect.w=2*toop.rad,sizerect.h=2*toop.rad;
    SDL_RenderCopy(renderer,maingame_ball[theme_ball],NULL,&sizerect);

    for(int i=0;i<ajor.size();i++)
    {
        if(ajor[i].strength>0)
        {
            sizerect.x=ajor[i].x,sizerect.y=ajor[i].y,sizerect.w=ajor[i].w,sizerect.h=ajor[i].h;
            if(ajor[i].strength<100)
                SDL_RenderCopy(renderer,maingame_brick[0],NULL,&sizerect);
            if(ajor[i].strength<10)
            {
                sizerect.x=ajor[i].x+ajor[i].w/2-5;
                sizerect.y=ajor[i].y+10;
                sizerect.w=10;
                sizerect.h=20;
                SDL_RenderCopy(renderer,digit[0][ajor[i].strength],NULL,&sizerect);
            }
            else if(ajor[i].strength<100)
            {
                sizerect.x=ajor[i].x+ajor[i].w/2-12;
                sizerect.y=ajor[i].y+10;
                sizerect.w=10;
                sizerect.h=20;
                SDL_RenderCopy(renderer,digit[0][ajor[i].strength/10],NULL,&sizerect);
                sizerect.x=ajor[i].x+ajor[i].w/2+2;
                sizerect.y=ajor[i].y+10;
                sizerect.w=10;
                sizerect.h=20;
                SDL_RenderCopy(renderer,digit[0][ajor[i].strength%10],NULL,&sizerect);
            }
            if(ajor[i].strength==100)
            {
                ///bomb
                sizerect.x=ajor[i].x,sizerect.y=ajor[i].y,sizerect.w=ajor[i].w,sizerect.h=ajor[i].h;
                SDL_RenderCopy(renderer,maingame_brick[1],NULL,&sizerect);
            }
            if(ajor[i].strength==101)
            {
                sizerect.x=ajor[i].x,sizerect.y=ajor[i].y,sizerect.w=ajor[i].w,sizerect.h=ajor[i].h;
                SDL_RenderCopy(renderer,maingame_brick[2],NULL,&sizerect);
            }

//            boxRGBA(renderer,ajor[i].x,ajor[i].y,ajor[i].x+ajor[i].w,ajor[i].y+ajor[i].h,216,151,16,255);
//            boxRGBA(renderer,ajor[i].x+1,ajor[i].y+1,ajor[i].x+ajor[i].w-1,ajor[i].y+ajor[i].h-1,220,72,1,255);
        }
    }
    sizerect.x=1120,sizerect.y=150,sizerect.w=66,sizerect.h=20;
    SDL_RenderCopy(renderer,maingame_live[0],NULL,&sizerect);
    sizerect.x=1120,sizerect.y=200,sizerect.w=84,sizerect.h=20;
    SDL_RenderCopy(renderer,maingame_level[0],NULL,&sizerect);
    sizerect.x=1120,sizerect.y=250,sizerect.w=84,sizerect.h=20;
    SDL_RenderCopy(renderer,maingame_score[0],NULL,&sizerect);
    sizerect.x=1120,sizerect.y=300,sizerect.w=100,sizerect.h=20;
    SDL_RenderCopy(renderer,maingame_damage[0],NULL,&sizerect);

    drawdigi(renderer,Lives,150);
    drawdigi(renderer,level,200);
    drawdigi(renderer,scores,250);
    drawdigi(renderer,damage,300);


    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}

bool rect_barkhord(brick a,brick b)
{
    int x1,x2,y1,y2;
    x1=a.x+a.w/2;
    y1=a.y+a.h/2;
    x2=b.x+b.w/2;
    y2=b.y+b.h/2;
    int dw=abs(x1-x2),dh=abs(y1-y2);

    if((dw<=a.w+1 && dh==0) || (dw==0 && dh<=a.h+1) || (dw>0 && dh>0 && dw*dw+dh*dh<=a.w*a.w+a.h*a.h+1))
        return 1;
    return 0;
}

void checkbrick(brick *a,ball *b,int *damage)
{
    bool barkhord=0;
    brick blook=*a;
    ball toop=*b;
    int left,right,up,down;
    left=blook.x-toop.x;
    right=toop.x-(blook.x+blook.w);
    up=blook.y-toop.y;
    down=toop.y-(blook.y+blook.h);
    if(up>=0)
    {
        if(right>0)
        {
            if(right*right+up*up<=toop.rad*toop.rad)
                toop.stpx*=-1,toop.stpy*=-1,barkhord=1;
        }
        else if(left>0)
        {
            if(left*left+up*up<=toop.rad*toop.rad)
                toop.stpx*=-1,toop.stpy*=-1,barkhord=1;
        }
        else
        {
            if(up<=toop.rad)
                toop.stpy*=-1,barkhord=1;
        }
    }
    else if(down>=0)
    {
        if(right>0)
        {
            if(right*right+down*down<=toop.rad*toop.rad)
                toop.stpx*=-1,toop.stpy*=-1,barkhord=1;
        }
        else if(left>0)
        {
            if(left*left+down*down<=toop.rad*toop.rad)
                toop.stpx*=-1,toop.stpy*=-1,barkhord=1;
        }
        else
        {
            if(down<=toop.rad)
                toop.stpy*=-1,barkhord=1;
        }
    }
    else
    {
        if(left>=0 && left<=toop.rad)
            toop.stpx*=-1,barkhord=1;
        if(right>=0 && right<=toop.rad)
            toop.stpx*=-1,barkhord=1;
    }
    if(barkhord)
    {
        if(blook.strength<100)
        {
//            Mix_PlayChannel(-1,chik,0);
            int k=min(*damage,blook.strength);
            blook.strength-=k;
            *damage-=k;
        }
        if(blook.strength==100)
        {
//            Mix_PlayChannel(-1,bomb_sound,0);
            blook.strength=0;
            for(int i=0;i<ajor.size();i++)
            {
                if(rect_barkhord(ajor[i],blook))
                    ajor[i].strength=0;
            }

        }
        if(blook.strength==101)
        {
            blook.strength=0;
            Lives++;
//            Mix_PlayChannel(-1,live_sound,0);
        }
    }
    *a=blook;
    *b=toop;
    return ;
}

void baztab(int w0,double *vx,double *vy)
{
    int p=w0-((t1.w)/2);
    //int g=w0-p;
    double v=sqrt((*vx)*(*vx)+(*vy)*(*vy));
    double tetamin=M_PI/6;
    double teta=((2*tetamin-M_PI)/t1.w)*fabs(p)+M_PI/2;
    *vx=v*cos(teta);
    *vy=-1*v*sin(teta);
    if(p<0)
        (*vx)*=-1;
}
int checkt1(board *a,ball *b)
{
    bool z=0;
    board t1=*a;
    ball toop=*b;
    double left,right,up,down;
    left=t1.x-toop.x;
    right=toop.x-(t1.x+t1.w);
    up=t1.y-toop.y;
    down=toop.y-(t1.y+t1.h);
    if(up>=0)
    {
        if(right>=0)
        {
            if(right*right+up*up<=toop.rad*toop.rad)
            {
                baztab(t1.w,&toop.stpx,&toop.stpy),z=1;
            }
        }
        else if(left>=0)
        {
            if(left*left+up*up<=toop.rad*toop.rad)
            {
                baztab(0,&toop.stpx,&toop.stpy),z=1;
            }
        }
        else
        {
            if(up<=toop.rad)
                baztab(-1*left,&toop.stpx,&toop.stpy),z=1;
        }
    }
    else if(down>=0)
    {
        if(right>=0)
        {
            if(right*right+down*down<=toop.rad*toop.rad)
            {
                toop.stpx*=-1,z=1;
                toop.stpy*=-1;
            }
        }
        else if(left>=0)
        {
            if(left*left+down*down<=toop.rad*toop.rad)
            {
                toop.stpx*=-1,z=1;
                toop.stpy*=-1;
            }
        }
        else
        {
            if(down<=toop.rad)
                toop.stpy*=-1,z=1;
        }
    }
    else
    {
        if(left>=0 && left<=toop.rad)
            toop.stpx*=-1,z=1;
        if(right>=0 && right<=toop.rad)
            toop.stpx*=-1,z=1;
    }
    *b=toop;
    if(z)
    {
//        Mix_PlayChannel(-1,chik,0);
    }

}
bool shiftbrick(int k)
{
    srand(time(NULL));
    int chance;
    bool lose=0;
        while(k--)
        {
            for(int i=0;i<ajor.size();i++)
            {
                ajor[i].y+=ajor[i].h;
                if(ajor[i].y>=H-180)
                    lose=1;
            }
            for(int i=0;i<num_of_brick;i++)
            {
                brick a;
                a.h=40,a.w=75;
                a.x=i*a.w+w0;
                a.y=h0;
                chance=rand()%100+1;
                if(chance<=90)
                    a.strength=rand()%(level+1);
                else if(chance<=95)
                    a.strength=100;
                else if(chance<=100)
                    a.strength=101;
                if(a.strength!=0)
                    ajor.push_back(a);
            }
        }
        return lose;
}
int maingame_01player(SDL_Renderer * renderer)
{
    const Uint8 *state=SDL_GetKeyboardState(NULL);//keyboard Scan
    max_w=1069;
    hmax=40;
    t1.h=15,t1.w=150,t1.y=H-hmax,t1.x=max_w/2-t1.w/2;
    toop.rad=10,toop.stpx=1,toop.stpy=-1,toop.x=max_w/2,toop.y=H-(hmax+toop.rad);
    string address="codegame/"+int_to_string(current_codegame)+".txt";
    if(newgame==1)
    {
        string s="player_codegame/"+name_current_player+".txt";
        fstream player_codegame;
        player_codegame.open(s.c_str(),ios::out | ios::app);
        player_codegame.seekp(0);
        player_codegame<<endl;
        player_codegame.seekp(0);
        player_codegame<<current_codegame<<" ";
        Lives=3,level=1,scores=0,damage=level*(4-difficulty);
        while(ajor.size())
            ajor.pop_back();
    }
    else
    {
        while(ajor.size())
            ajor.pop_back();
        fstream codegame;
        int num;
        codegame.open(address.c_str());
        codegame>>Lives>>level>>scores>>damage>>difficulty>>num;
        for(int i=0;i<num;i++)
        {
            brick a;
            a.h=40,a.w=75;
            codegame>>a.x>>a.y>>a.strength;
            ajor.push_back(a);
        }
    }
    int cheat[6];
    int letkey[26];
    string pak="AAAAAA";
    for(int i=0;i<26;i++)
        letkey[i]=0;
    for(int i=0;i<5;i++)
        cheat[i]=-1;
    drawframe(renderer);
    bool start=0;
    POINT mouse;
    SetCursorPos(max_w/2-t1.w/2,H-hmax);
    bool letstop=1;
    bool lose=0;
    ShowCursor(false);
    while(true)
    {
      //  ShowCursor(false);
        SDL_PumpEvents();
        for(int i=4;i<=29;i++)
            if(letkey[i-4] && (state[i]))
                cheat[5]=cheat[4],cheat[4]=cheat[3],cheat[3]=cheat[2],cheat[2]=cheat[1],cheat[1]=cheat[0],cheat[0]=i-4,letkey[i-4]=0;
            else if (!state[i])
                letkey[i-4]=1;
        string cheatcode;
        for(int i=5;i>=0;i--)
            cheatcode+=char(cheat[i]+'a');
        // health clearb
        if(cheatcode=="health")
        {
            Lives++;
            for(int i=0;i<6;i++)
                cheat[i]=-1;
        }
        if(cheatcode=="clearb")
        {
            while(ajor.size())
                ajor.pop_back();
            for(int i=0;i<6;i++)
                cheat[i]=-1;
        }

        if(Lives==0)
        {
            lose=1;
        }
        if(toop.y>=H+toop.rad)
        {
            Lives--;
            start=0;
            SetCursorPos(max_w/2-t1.w/2,H-hmax);
        }
        for(int i=0;i<ajor.size();i++)
        {
            if(damage!=0)
                checkbrick(&(ajor[i]),&toop,&damage);
            for(int i=0;i<ajor.size();i++)
                if(ajor[i].strength==0)
                {
                    scores+=level;
                    swap(ajor[i],ajor[ajor.size()-1]),ajor.pop_back(),i--;
                }
            if(!damage)
            {
                break ;
            }
        }
        if(!damage)
        {
            level++;
            if(shiftbrick(1))
                lose=1;
            start=0;
            damage=level*(4-difficulty);
        }
        if(ajor.size()==0)
        {
            scores+=100*level;
            shiftbrick(3);
            start=0;
        }
        if(theme_control==1)
        {
        /* control with keyboard*/
            t1.stpx=0;
            if(state[SDL_SCANCODE_A])
                t1.stpx+=-1;
            if(state[SDL_SCANCODE_D])
                t1.stpx+=+1;
           if(state[SDL_SCANCODE_SPACE])
                start=1;
        }
        else
        {
            GetCursorPos(&mouse);
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                start=1;
            if(mouse.x>max_w-t1.w)
                SetCursorPos(max_w-t1.w,H-hmax),t1.x=max_w-t1.w;
            else if(mouse.x<=20)
                SetCursorPos(20,H-hmax),t1.x=20;
            else
                t1.x=mouse.x;
        }
        if(state[SDL_SCANCODE_ESCAPE])
        {
            if(letstop)
            {
                ShowCursor(true);
                int c=stopmenu(renderer);
                if(c)
                    return c-1;
                letstop=0;
                ShowCursor(false);
                SetCursorPos(mouse.x,mouse.y);
//                ShowCursor(false);
            }
        }
        else
            letstop=1;
        /// okay
        if((toop.x>=w0+toop.rad-2 &&toop.x<w0+toop.rad) || (toop.x>=max_w-(toop.rad) && toop.x<=max_w-toop.rad+3))
            toop.stpx*=-1;
        if((toop.y<h0+toop.rad && toop.y>=h0+toop.rad-2))
            toop.stpy*=-1;
        if(start && !(toop.stpx==1 && toop.stpy==-1))
            checkt1(&t1,&toop);
        else
            toop.stpx=+1,toop.stpy=-1;
        /// emal command
        if(t1.x+t1.stpx>0 && t1.x+t1.stpx<max_w-t1.w)
            t1.x+=t1.stpx;
        if(start==1)
        {
            toop.x+=toop.stpx;
            toop.y+=toop.stpy;
        }
        else
        {
            toop.y=H-(hmax+toop.rad);
            toop.x=t1.x+t1.w/2;
        }
        /// okay
        drawframe(renderer);
        if(lose==1)
            break ;
    }
    fstream highscore;
    highscore.open("highscore.txt");
    string esm[5];
    int sc[5];
    for(int i=0;i<5;i++)
    {
        highscore>>esm[i];
        highscore>>sc[i];
    }
    highscore.close();
    for(int i=0;i<5;i++)
    {
        if(scores>=sc[i])
        {
            sc[4]=scores;
            esm[4]=name_current_player;
            for(int j=4;j>i;j--)
                swap(sc[j],sc[j-1]),swap(esm[j],esm[j-1]);
            break ;
        }
    }
    highscore.open("highscore.txt",ios::out | ios::trunc);
    for(int i=0;i<5;i++)
        highscore<<esm[i]<<" "<<sc[i]<<" ";
    SDL_Rect sizerect;
    sizerect.x=0,sizerect.y=0,sizerect.h=H,sizerect.w=W;
    SDL_RenderCopy(renderer,mainmenu_background[0],NULL,&sizerect);
    highscore.close();
    ShowCursor(true);
    return 1;
}
//}
//{ *main function*
int main( int argc, char * argv[] )
{
    /// create window , renderer and load texture and surface
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO;
    SDL_Init( SDL_flags );

    Uint32 WND_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;

    SDL_Window *window01;
    SDL_Renderer *renderer01;
    SDL_CreateWindowAndRenderer( 1366, 768 , WND_flags, &window01, &renderer01 );
    SDL_RaiseWindow(window01);
    SDL_RaiseWindow(window01);

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    W = DM.w,H = DM.h;//get window size
    /// okay
//    button_texture[0]=IMG_LoadTexture(renderer01,"button.png");
    SDL_SetRenderDrawColor(renderer01,0,0,0,255);
    SDL_RenderClear(renderer01);
    SDL_Texture *start_background=IMG_LoadTexture(renderer01,"start_background.png");
    SDL_Rect sizerect;
    sizerect.x=0,sizerect.y=0,sizerect.w=W,sizerect.h=H;
    SDL_RenderCopy(renderer01,start_background,NULL,&sizerect);
    SDL_RenderPresent(renderer01);

//    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
//    Mix_Music  *background_music=Mix_LoadMUS("background_music.mp3");
//    chik=Mix_LoadWAV("chik.WAV");
//    bomb_sound=Mix_LoadWAV("bomb_sound.WAV");
//    live_sound=Mix_LoadWAV("live_sound.WAV");
//    Mix_PlayMusic(background_music,-1);
//    Mix_VolumeMusic(20);
//    Mix_VolumeChunk(chik,100);
//    Mix_VolumeChunk(bomb_sound,100);
//    Mix_VolumeChunk(live_sound,100);



    fstream file_theme;
    file_theme.open("theme.txt");
    file_theme>>createcodegame;
    file_theme>>theme_ball;
    file_theme>>theme_board;
    file_theme>>theme_control;
    file_theme.close();

    optionmenu_page[0]=IMG_LoadTexture(renderer01,"optionmenu_page_theme1.png");

    string a;
    char c;
    for(int i=0;i<26;i++)
    {
        a="alfabet/";
        c='a'+i;
        a+=c;
        a+=".png";
        alfabet[i]=IMG_LoadTexture(renderer01,a.c_str());
    }


    startmenu_background[0]=IMG_LoadTexture(renderer01,"startmenu_background_theme1.png");

    playmenu_page[0]=IMG_LoadTexture(renderer01,"playmenu_page_theme1.png");
    playmenu_button_newgame[0][0]=IMG_LoadTexture(renderer01,"playmenu_button_newgame_unpressed_theme1.png");
    playmenu_button_loadgame[0][0]=IMG_LoadTexture(renderer01,"playmenu_button_loadgame_unpressed_theme1.png");
    playmenu_button_option[0][0]=IMG_LoadTexture(renderer01,"playmenu_button_option_unpressed_theme1.png");
    playmenu_button_mainmenu[0][0]=IMG_LoadTexture(renderer01,"playmenu_button_mainmenu_unpressed_theme1.png");

    playmenu_button_newgame[0][1]=IMG_LoadTexture(renderer01,"playmenu_button_newgame_pressed_theme1.png");
    playmenu_button_loadgame[0][1]=IMG_LoadTexture(renderer01,"playmenu_button_loadgame_pressed_theme1.png");
    playmenu_button_option[0][1]=IMG_LoadTexture(renderer01,"playmenu_button_option_pressed_theme1.png");
    playmenu_button_mainmenu[0][1]=IMG_LoadTexture(renderer01,"playmenu_button_mainmenu_pressed_theme1.png");

    mainmenu_background[0]=IMG_LoadTexture(renderer01,"mainmenu_background_theme1.png");
    mainmenu_page[0]=IMG_LoadTexture(renderer01,"mainmenu_page_theme1.png");

    mainmenu_button_start[0][1]=IMG_LoadTexture(renderer01,"mainmenu_button_start_pressed_theme1.png");
    mainmenu_button_option[0][1]=IMG_LoadTexture(renderer01,"mainmenu_button_option_pressed_theme1.png");
    mainmenu_button_highscore[0][1]=IMG_LoadTexture(renderer01,"mainmenu_button_highscores_pressed_theme1.png");
    mainmenu_button_credit[0][1]=IMG_LoadTexture(renderer01,"mainmenu_button_credit_pressed_theme1.png");
    mainmenu_button_help[0][1]=IMG_LoadTexture(renderer01,"mainmenu_button_help_pressed_theme1.png");
    mainmenu_button_exit[0][1]=IMG_LoadTexture(renderer01,"mainmenu_button_exit_pressed_theme1.png");

    mainmenu_button_start[0][0]=IMG_LoadTexture(renderer01,"mainmenu_button_start_unpressed_theme1.png");
    mainmenu_button_option[0][0]=IMG_LoadTexture(renderer01,"mainmenu_button_option_unpressed_theme1.png");
    mainmenu_button_highscore[0][0]=IMG_LoadTexture(renderer01,"mainmenu_button_highscores_unpressed_theme1.png");
    mainmenu_button_credit[0][0]=IMG_LoadTexture(renderer01,"mainmenu_button_credit_unpressed_theme1.png");
    mainmenu_button_help[0][0]=IMG_LoadTexture(renderer01,"mainmenu_button_help_unpressed_theme1.png");
    mainmenu_button_exit[0][0]=IMG_LoadTexture(renderer01,"mainmenu_button_exit_unpressed_theme1.png");


    maingame_damage[0]=IMG_LoadTexture(renderer01,"maingame_damage_theme1.png");
    maingame_level[0]=IMG_LoadTexture(renderer01,"maingame_level_theme1.png");
    maingame_score[0]=IMG_LoadTexture(renderer01,"maingame_score_theme1.png");
    maingame_live[0]=IMG_LoadTexture(renderer01,"maingame_live_theme1.png");

    stopmenu_page[0]=IMG_LoadTexture(renderer01,"stopmenu_page_theme1.png");
    stopmenu_button_resume[0][0]=IMG_LoadTexture(renderer01,"stopmenu_button_resume_unpressed_theme1.png");
    stopmenu_button_savegame[0][0]=IMG_LoadTexture(renderer01,"stopmenu_button_savegame_unpressed_theme1.png");
    stopmenu_button_loadgame[0][0]=IMG_LoadTexture(renderer01,"stopmenu_button_loadgame_unpressed_theme1.png");
    stopmenu_button_option[0][0]=IMG_LoadTexture(renderer01,"stopmenu_button_option_unpressed_theme1.png");
    stopmenu_button_playermenu[0][0]=IMG_LoadTexture(renderer01,"stopmenu_button_playermenu_unpressed_theme1.png");
    stopmenu_button_resume[0][1]=IMG_LoadTexture(renderer01,"stopmenu_button_resume_pressed_theme1.png");
    stopmenu_button_savegame[0][1]=IMG_LoadTexture(renderer01,"stopmenu_button_savegame_pressed_theme1.png");
    stopmenu_button_loadgame[0][1]=IMG_LoadTexture(renderer01,"stopmenu_button_loadgame_pressed_theme1.png");
    stopmenu_button_option[0][1]=IMG_LoadTexture(renderer01,"stopmenu_button_option_pressed_theme1.png");
    stopmenu_button_playermenu[0][1]=IMG_LoadTexture(renderer01,"stopmenu_button_playermenu_pressed_theme1.png");



    digit[0][0]=IMG_LoadTexture(renderer01,"digit/0.png");
    digit[0][1]=IMG_LoadTexture(renderer01,"digit/1.png");
    digit[0][2]=IMG_LoadTexture(renderer01,"digit/2.png");
    digit[0][3]=IMG_LoadTexture(renderer01,"digit/3.png");
    digit[0][4]=IMG_LoadTexture(renderer01,"digit/4.png");
    digit[0][5]=IMG_LoadTexture(renderer01,"digit/5.png");
    digit[0][6]=IMG_LoadTexture(renderer01,"digit/6.png");
    digit[0][7]=IMG_LoadTexture(renderer01,"digit/7.png");
    digit[0][8]=IMG_LoadTexture(renderer01,"digit/8.png");
    digit[0][9]=IMG_LoadTexture(renderer01,"digit/9.png");

    maingame_background[0]=IMG_LoadTexture(renderer01,"maingame_background_theme1.png");
    maingame_brick[0]=IMG_LoadTexture(renderer01,"maingame_brick_theme1.png");
    maingame_brick[1]=IMG_LoadTexture(renderer01,"maingame_brick_theme2.png");
    maingame_brick[2]=IMG_LoadTexture(renderer01,"maingame_brick_theme3.png");
    maingame_ball[0]=IMG_LoadTexture(renderer01,"maingame_ball_theme1.png");
    maingame_ball[1]=IMG_LoadTexture(renderer01,"maingame_ball_theme2.png");
    maingame_ball[2]=IMG_LoadTexture(renderer01,"maingame_ball_theme3.png");
    maingame_ball[3]=IMG_LoadTexture(renderer01,"maingame_ball_theme4.png");
    maingame_board[0]=IMG_LoadTexture(renderer01,"maingame_board_theme1.png");
    maingame_board[1]=IMG_LoadTexture(renderer01,"maingame_board_theme2.png");
    maingame_board[2]=IMG_LoadTexture(renderer01,"maingame_board_theme3.png");
    maingame_board[3]=IMG_LoadTexture(renderer01,"maingame_board_theme4.png");

    stopmenu_page[0]=IMG_LoadTexture(renderer01,"stopmenu_page_theme1.png");

    //optionmenu(renderer01);
    //startmenu(renderer01);
    //maingame_01player(renderer01);
    mainmenu(renderer01);
    //playmenu(renderer01);
    //stopmenu(renderer01);

    file_theme.open("theme.txt",ios::out | ios::trunc);
    file_theme<<createcodegame<<" "<<theme_ball<<" "<<theme_board<<" "<<theme_control;
    file_theme.close();

    /// delete  and quit window , renderer , ...
//    Mix_FreeMusic(background_music);
    SDL_DestroyWindow( window01 );
    SDL_DestroyRenderer( renderer01 );
	IMG_Quit();
	SDL_Quit();
	/// okay
    return 0;

}
//}
