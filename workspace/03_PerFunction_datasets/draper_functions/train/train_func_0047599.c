main(int argc, const char * argv[]) {
    int run = 0;
    char * config_file = NULL;
    FILE * config = NULL;
    int optchar = 0;

    config_file = find_config_file();
    dbg_init(stderr, 0, 1);

    DBG(0, "setup signals\n");
    setup_signals();

    do {
        optchar = getopt(argc, (char * const *) argv, "f:h");
        switch (optchar) {
            case 'f':
                DBG(0, "user defined config file: %s\n", optarg);
                if (NULL != config_file)
                    free(config_file);
                config_file = strdup(optarg);
                break;
            case 'h':
            case '?':
                show_help();
                goto do_cleanup;
                break;
            default:
                break;
        }

    } while (optchar != -1);

    DBG(0, "prepare config file: %s\n", config_file);
    config = prepare_config(config_file);
    if (NULL == config)
        goto do_cleanup;

    DBG(0, "init uish\n");
    if (uish_init(&uish, argv[0], "% ", config))
        run = 1;

    close_config(config);

    DBG(0, "enter input loop, run: %d\n", run);
    while (run) {
        res_status_t res = RES_CONTINUE;
        res = uish_handle_input(&uish);
        if (res == RES_EXIT) {
            run = 0;
            continue;
        }
    }

    uish_end(&uish);
do_cleanup:
    DBG(0, "cleanup\n");
    free(config_file);
    return 0;
}
