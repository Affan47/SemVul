main(int argc, char **argv)
{
    int i;
    struct sigaction act;

    setlocale(LC_ALL, "");
    read_config(NULL);

    for (i = 1; i < argc; i++) {
        if ARG("config", "rc", 1) {
            read_config(argv[++i]);
        } else if ARG("font", "fn", 1) {
            opt_font = argv[++i];
#ifdef XFT
        } else if ARG("xftfont", "fa", 1) {
            opt_xftfont = argv[++i];
#endif
        } else if ARG("fgcolor", "fg", 1) {
            opt_fg = argv[++i];
        } else if ARG("bgcolor", "bg", 1) {
            opt_bg = argv[++i];
        } else if ARG("bdcolor", "bd", 1) {
            opt_bd = argv[++i];
        } else if ARG("bdwidth", "bw", 1) {
            opt_bw = atoi(argv[++i]);
        } else if ARG("padding", "p", 1) {
            opt_pad = atoi(argv[++i]);
        } else if ARG("imap", "i", 0) {
            opt_imap = 1;
        } else if ARG("no-imap", "n", 0) {
            opt_imap = 0;
        } else if ARG("new1", "1", 1) {
            opt_new[0] = argv[++i];
        } else if ARG("new2", "2", 1) {
            opt_new[1] = argv[++i];
        } else if ARG("new3", "3", 1) {
            opt_new[2] = argv[++i];
        } else if ARG("new4", "4", 1) {
            opt_new[3] = argv[++i];
        } else if ARG("new5", "5", 1) {
            opt_new[4] = argv[++i];
        } else if ARG("version", "v",0) {
            printf("aewm: version " VERSION "\n");
            exit(0);
        } else if ARG("help", "h",0) {
            printf(USAGE);
            exit(0);
        } else {
            fprintf(stderr, "aewm: unknown option: '%s'\n" USAGE, argv[i]);
            exit(2);
        }
    }

    act.sa_handler = sig_handler;
    act.sa_flags = 0;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);

    setup_display();
    event_loop();
    return 0;
}
