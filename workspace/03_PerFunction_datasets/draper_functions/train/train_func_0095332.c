main(int argc, char **argv)
{
    char *pidfile;

    setproctitle_init(argc, argv);

    openlog("ovdb_monitor", L_OPENLOG_FLAGS | LOG_PID, LOG_INN_PROG);
    message_program_name = "ovdb_monitor";

    if(argc != 2 || strcmp(argv[1], SPACES))
        die("should be started by ovdb_init");
    message_handlers_warn(1, message_log_syslog_err);
    message_handlers_die(1, message_log_syslog_err);

    if (!innconf_read(NULL))
	exit(1);

    if(strcmp(innconf->ovmethod, "ovdb"))
        die("ovmethod not set to ovdb in inn.conf");
    if(!ovdb_check_user())
        die("command must be run as runasuser user");
    if(!ovdb_getlock(OVDB_LOCK_ADMIN))
        die("cannot lock database");

    xsignal(SIGINT, sigfunc);
    xsignal(SIGTERM, sigfunc);
    xsignal(SIGHUP, sigfunc);

    pidfile = concatpath(innconf->pathrun, OVDB_MONITOR_PIDFILE);
    if(putpid(pidfile))
	exit(1);
    if(start_process(&deadlockpid, deadlock))
	cleanup(1);
    if(start_process(&checkpointpid, checkpoint))
	cleanup(1);
    if(start_process(&logremoverpid, logremover))
	cleanup(1);

    monitorloop();


    return 1;
}
