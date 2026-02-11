service_init(int argc __attribute__((unused)),
		 char **argv __attribute__((unused)),
		 char **envp __attribute__((unused)))
{
    int opt, r;

    if (geteuid() == 0) fatal("must run as the Cyrus user", EC_USAGE);
    setproctitle_init(argc, argv, envp);


    signals_set_shutdown(&shut_down);
    signal(SIGPIPE, SIG_IGN);


    global_sasl_init(1, 1, mysasl_cb);

    while ((opt = getopt(argc, argv, "p:")) != EOF) {
	switch(opt) {
	case 'p':
	    extprops_ssf = atoi(optarg);
	    break;
	default:
	    usage();
	}
    }


    if ((r = mboxname_init_namespace(sync_namespacep, 1)) != 0) {
        fatal(error_message(r), EC_CONFIG);
    }


    mboxlist_init(0);
    mboxlist_open(NULL);


    quotadb_init(0);
    quotadb_open(NULL);


    annotatemore_init(0, NULL, NULL);
    annotatemore_open(NULL);


    if (config_getswitch(IMAPOPT_STATUSCACHE)) {
	statuscache_open(NULL);
    }

    return 0;
}
