run()
{

    WorldDatabase.ThreadStart();

    char commandbuf[256];


    sLog.outString();

    if (sConfig.GetBoolDefault("BeepAtStart", true))
        printf("\a");


    printf("mangos>");


    while (!World::IsStopped())
    {
        fflush(stdout);
#ifdef linux
        while (!kb_hit_return() && !World::IsStopped())

            usleep(100);
        if (World::IsStopped())
            break;
#endif
        char* command_str = fgets(commandbuf, sizeof(commandbuf), stdin);
        if (command_str != NULL)
        {
            for (int x = 0; command_str[x]; ++x)
                if (command_str[x] == '\r' || command_str[x] == '\n')
                {
                    command_str[x] = 0;
                    break;
                }

            if (!*command_str)
            {
                printf("mangos>");
                continue;
            }

            std::string command;
            if (!consoleToUtf8(command_str, command))
            {
                printf("mangos>");
                continue;
            }

            sWorld.QueueCliCommand(new CliCommandHolder(0, SEC_CONSOLE, NULL, command.c_str(), &utf8print, &commandFinished));
        }
        else if (feof(stdin))
        {
            World::StopNow(SHUTDOWN_EXIT_CODE);
        }
    }


    WorldDatabase.ThreadEnd();
}
