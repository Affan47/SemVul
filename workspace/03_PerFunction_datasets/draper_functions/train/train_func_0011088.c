CheckCheat(UBYTE c )
{
    static int cheat_counter=0,current_cheat=-1;
    int i;

    if(current_cheat>=0)
    {
        if(cheats[current_cheat][cheat_counter]==c)
        {
            cheat_counter++;

            if(cheat_counter==(int)strlen(cheats[current_cheat]))
            {
                if(!menusound[0])
                    menusound[0]=LoadSound(menu_soundname[0]);

                if(menusound[0])
                    PlayBackSound(menusound[0]);

                D(bug("Eseguo il cheat: %ld\n",current_cheat));

                switch(current_cheat)
                {
                    case 0:

                        if(current_menu==MENU_ARCADE_SELECTION)
                        {
                            *teamarray=ARCADE_TEAMS;
                            controllo[ARCADE_TEAMS]=1;
                            turno=0;
                            competition=MENU_CHALLENGE;
                            cb[0].ID=MENU_CHALLENGE;
                            SetupMatches();
                            ChangeMenu(MENU_CHALLENGE);
                        }
                        break;

                    case 1:
                        final=TRUE;
                        break;
                    case 2:
                        framerate=35;
                        break;
                    case 3:
                        framerate=15;
                        break;
                    case 4:
                        nopari=TRUE;
                        break;
                    case 5:
                        killer=TRUE;
                        break;
                    case 6:
                        warp=TRUE;
                        break;
#ifdef CD_VERSION
                    case 7:
                        Outro();
                        break;
#endif
                }
            }

            return;
        }
        else
        {
            D(bug("Cheat errato: %ld...(%lc invece di %lc al char %ld)\n",current_cheat,c,cheats[current_cheat][cheat_counter],cheat_counter));
            current_cheat=-1;
            cheat_counter=0;
        }
    }

    for(i=0;i<NUMERO_CHEAT;i++)
    {
        if(c==*cheats[i])
        {
            current_cheat=i;
            cheat_counter=1;
            D(bug("Probabile cheat: %ld\n",i));
            return;
        }
    }
}
