parse_command_line(Config *c, int argc, char *argv[]) {
    int o;

    static const struct option long_options[] = {
        { "help",           no_argument,       NULL, 'h' },
        { "ssh",            no_argument,       NULL, 's' },
        { "vnc",            no_argument,       NULL, 'v' },
        { "shell",          no_argument,       NULL, 'S' },
        { "domain",         required_argument, NULL, 'd' },
        { NULL, 0, NULL, 0 }
    };

    while ((o = getopt_long(argc, argv, "hVd:svS", long_options, NULL)) >= 0) {

        switch(o) {
            case 'h':
                c->command = COMMAND_HELP;
                break;
            case 's':
                c->command = COMMAND_SSH;
                break;
            case 'v':
                c->command = COMMAND_VNC;
                break;
            case 'S':
                c->command = COMMAND_SHELL;
                break;
            case 'd':
                avahi_free(c->domain);
                c->domain = avahi_strdup(optarg);
                break;
            default:
                return -1;
        }
    }

    if (optind < argc) {
        fprintf(stderr, _("Too many arguments\n"));
        return -1;
    }

    return 0;
}
