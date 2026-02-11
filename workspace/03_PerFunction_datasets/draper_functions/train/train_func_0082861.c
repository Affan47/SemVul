main(int argc, char *argv[])
{
    main_arginit(argv[0]);
    main_args(argc, argv);
    main_confdir(ConfDir, sizeof(ConfDir), ConfPath);
    main_init_signal();

    plog(LOG_DEBUG, "%s: confdir = %s", __func__, ConfDir);

    if (!Options.opt_foreground) {
        plog_setflag(DNS_LOG_FLAG_SYSLOG);
        if (daemon(0, 0) < 0) {
            plog_error(LOG_ERR, MODULE, "daemon() failed");
            return EXIT_FAILURE;
        }
    }

    if (dns_config_update(Options.opt_config) < 0)
        return EXIT_FAILURE;

    if (main_init() < 0)
        return EXIT_FAILURE;
    if (main_make_pidfile() < 0)
        return EXIT_FAILURE;
    if (dns_util_setugid(Options.opt_user, Options.opt_group) < 0)
        return EXIT_FAILURE;

    if (dns_sock_start_thread() < 0)
        return EXIT_FAILURE;
    if (dns_control_start_thread() < 0)
        return EXIT_FAILURE;
    if (dns_session_start_thread(Options.opt_threads) < 0)
        return EXIT_FAILURE;

    plog(LOG_INFO, "%s started", PROGNAME);
    dns_config_notify_all_engines();
    dns_notify_all_slaves();
    main_loop();

    return EXIT_SUCCESS;
}
