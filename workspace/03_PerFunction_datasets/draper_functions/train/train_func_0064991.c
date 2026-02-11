main(int argc, char** argv) {
    int i;
    vector<string> wu_names;

    for (i=1; i<argc; i++) {
        if (is_arg(argv[i], "cushion")) {
            if (!argv[++i]) {
                log_messages.printf(MSG_CRITICAL, "%s requires an argument\n\n", argv[--i]);
                usage(argv[0]);
                exit(1);
            }
            cushion = atoi(argv[i]);
        } else if (is_arg(argv[i], "d")) {
            if (!argv[++i]) {
                log_messages.printf(MSG_CRITICAL, "%s requires an argument\n\n", argv[--i]);
                usage(argv[0]);
                exit(1);
            }
            int dl = atoi(argv[i]);
            log_messages.set_debug_level(dl);
            if (dl == 4) g_print_queries = true;
        } else if (is_arg(argv[i], "wu_name")) {
            if (!argv[++i]) {
                log_messages.printf(MSG_CRITICAL, "%s requires an argument\n\n", argv[--i]);
                usage(argv[0]);
                exit(1);
            }
            wu_names.push_back(string(argv[i]));
        } else if (is_arg(argv[i], "max_wus")) {
            if (!argv[++i]) {
                log_messages.printf(MSG_CRITICAL, "%s requires an argument\n\n", argv[--i]);
                usage(argv[0]);
                exit(1);
            }
            max_wus = atoi(argv[i]);
        } else if (is_arg(argv[i], "one_pass")) {
            one_pass = true;
        } else if (is_arg(argv[1], "h") || is_arg(argv[1], "help")) {
            usage(argv[0]);
            exit(0);
        } else if (is_arg(argv[1], "v") || is_arg(argv[1], "version")) {
            printf("%s\n", SVN_VERSION);
            exit(0);
        } else {
            log_messages.printf(MSG_CRITICAL, "unknown command line argument: %s\n\n", argv[i]);
            usage(argv[0]);
            exit(1);
        }
    }
    check_stop_daemons();

    if (!wu_names.size()) {
        fprintf(stderr, "Must supply at least one WU name\n");
        exit(1);

    }

    log_messages.printf(MSG_NORMAL,
        "Starting: cushion %d, max_wus %d\n",
        cushion, max_wus
    );
    install_stop_signal_handler();

    srand48(getpid() + time(0));
    make_work(wu_names);
}
