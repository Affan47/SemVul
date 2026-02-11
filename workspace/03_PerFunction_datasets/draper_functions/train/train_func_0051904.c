main(int argc, char *argv[])
{
    sigset_t set;
    packet_handler = packet_dump;
    int statret;
    d_statfs_t s;

    sigemptyset(&set);
    sigprocmask(SIG_SETMASK, &set, NULL);


    signal(SIGTERM, quitter);    if(errno!=0) errno=0;
    signal(SIGINT, quitter);     if(errno!=0) errno=0;
    signal(SIGQUIT, quitter);    if(errno!=0) errno=0;
    signal(SIGHUP, restarter);   if(errno!=0) errno=0;
    signal(SIGALRM, dl_shutdown);  if(errno!=0) errno=0;

    rollsize = 2*GIGABYTE;

    logfilename = strdup("daemonlogger.pcap");

    parse_cmd_line(argc, argv);

    printf("\n-*> DaemonLogger <*-\n"
           "Version %s\n"
           "By Martin Roesch\n"
           "(C) Copyright 2006-2007 Sourcefire Inc., All rights reserved\n\n"
           , VERSION);

    if(showver) exit(0);

    if(logpath != NULL && !is_valid_path(logpath))
        fatal("Log path \"%s\" is bad", logpath);

    if(logpath != NULL)
    {
        snprintf(testpath, STDBUF-1, "%s/.", logpath);
        msg("Checking partition stats for log directory \"%s\"", testpath);
        if((statret = d_statfs(testpath, &s)) != 0)
        {
            fatal("Unable to stat partition!\n\"%s\"\n", strerror(statret));
        }
        else
        {
            if(maxpct)
            {
                double pct;
                double value;

                part_total_blocks = s.f_blocks;
                pct = ((double) maxpct)/100.0;
                value = ((double)part_total_blocks) * pct;
                part_min_free_blocks = part_total_blocks - ((u_int64_t) value);
                msg("%d%% max disk utilization = %llu blocks free (out of %llu)",
                    maxpct, part_min_free_blocks, part_total_blocks);
                rollsize_in_blocks = (u_int64_t) (rollsize/(size_t)s.f_bsize);
                msg("Blocksize = %lu", s.f_bsize);
                msg("Rollsize = %llu blocks\n", rollsize_in_blocks);
            }
        }
    }

    if(daemon_mode)
    {
        if(!is_valid_path(pidpath))
            fatal("PID path \"%s\" is bad, privilege problem usually",pidpath);

        openlog("daemonlogger", LOG_PID | LOG_CONS, LOG_DAEMON);
        go_daemon();
    }

    start_sniffing();
    if (rollover_interval != 0)
    {
        set_rollover_time();
    }

    sniff_loop();
    return 0;
}
