DoPause(void)
{
    BOOL ok=FALSE,was_stopped=TRUE;
    extern BOOL time_stopped;

    if(!time_stopped)
    {
        StopTime();
        was_stopped=FALSE;
    }

    pause_mode=TRUE;


    os_stop_audio();

    DrawPause();
    ScreenSwap();

    if(triple_buffering)
        ScreenSwap();

    while(!ok)
    {
        if(control[0]!=CTRL_JOYPAD && control[1]!=CTRL_JOYPAD)
        {
            os_wait();
        }
        else
        {
            os_delay(10);
            UpdatePortStatus();

            if( (MyReadPort0(0)&MYBUTTONMASK) ||
                (MyReadPort1(1)&MYBUTTONMASK) )
                ok=TRUE;
            else
                os_getevent();
        }

        ok=os_wait_end_pause()|ok;


        if(ok==2)
        {
            quit_game=TRUE;
            SetResult("break");

            if(p->team[0]->Joystick<0 ||
                p->team[1]->Joystick<0)
            {
                if(p->team[0]->Joystick>=0)
                {
                    p->team[0]->Reti=0;
                    p->team[1]->Reti=5;
                }
                else
                {
                    p->team[0]->Reti=5;
                    p->team[1]->Reti=0;
                }
            }
        }
    }

    os_start_audio();


    pause_mode=FALSE;

    if(!was_stopped)
        RestartTime();

    ideal=Timer()-1;
}
