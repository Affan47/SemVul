D_CheckNetGame (void)
{
    net_gamesettings_t settings;

    if (netgame)
    {
        autostart = true;
    }

    D_RegisterLoopCallbacks(&doom_loop_interface);

    SaveGameSettings(&settings);
    D_StartNetGame(&settings, NULL);
    LoadGameSettings(&settings);

    DEH_printf("startskill %i  deathmatch: %i  startmap: %i  startepisode: %i\n",
               startskill, deathmatch, startmap, startepisode);

    DEH_printf("player %i of %i (%i nodes)\n",
               consoleplayer+1, settings.num_players, settings.num_players);


    if (timelimit > 0 && deathmatch)
    {


        if (timelimit == 20 && M_CheckParm("-avg"))
        {
            DEH_printf("Austin Virtual Gaming: Levels will end "
                           "after 20 minutes\n");
        }
        else
        {
            DEH_printf("Levels will end after %d minute", timelimit);
            if (timelimit > 1)
                printf("s");
            printf(".\n");
        }
    }
}
