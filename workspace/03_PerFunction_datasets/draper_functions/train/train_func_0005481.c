main(int argc, char ** argv) {
#endif
    int c;
    int ind;
    const char * log_name = "-";
    const char * url = "TCP:";
    PeerServer * ps;
    ChannelServer * serv;

    ini_mdep();
    ini_trace();
    ini_events_queue();
    ini_asyncreq();

    log_mode = LOG_TCFLOG;

#if defined(_WRS_KERNEL)

    progname = "tcf";
    open_log_file("-");

#else

    progname = argv[0];


    for (ind = 1; ind < argc; ind++) {
        const char * s = argv[ind];
        if (*s != '-') {
            break;
        }
        s++;
        while ((c = *s++) != '\0') {
            switch (c) {
            case 'l':
            case 'L':
            case 's':
                if (*s == '\0') {
                    if (++ind >= argc) {
                        fprintf(stderr, "%s: error: no argument given to option '%c'\n", progname, c);
                        exit(1);
                    }
                    s = argv[ind];
                }
                switch (c) {
                case 'l':
                    log_mode = strtol(s, 0, 0);
                    break;

                case 'L':
                    log_name = s;
                    break;

                case 's':
                    url = s;
                    break;

                default:
                    fprintf(stderr, "%s: error: illegal option '%c'\n", progname, c);
                    exit(1);
                }
                s = "";
                break;

            default:
                fprintf(stderr, "%s: error: illegal option '%c'\n", progname, c);
                exit(1);
            }
        }
    }
    open_log_file(log_name);
    if (ind < argc) {
        dest_url = argv[ind++];
    }

#endif

    ps = channel_peer_from_url(url);
    if (ps == NULL) {
        fprintf(stderr, "%s: invalid server URL (-s option value): %s\n", progname, url);
        exit(1);
    }
    peer_server_addprop(ps, loc_strdup("Name"), loc_strdup("TCF Protocol Logger"));
    peer_server_addprop(ps, loc_strdup("Proxy"), loc_strdup(""));
    serv = channel_server(ps);
    if (serv == NULL) {
        fprintf(stderr, "%s: cannot create TCF server: %s\n", progname, errno_to_str(errno));
        exit(1);
    }
    serv->new_conn = channel_new_connection;

    discovery_start();


    run_event_loop();
    return 0;
}
