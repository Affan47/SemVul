parse_options(int argc, char *argv[])
{
    static const char optstr[] = "VhvnfpotcmMx:i:";
#ifdef HAVE_GETOPT_LONG
    static const struct option long_options[] = {
        {"version", no_argument, NULL, 'V'},
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"dry-run", no_argument, NULL, 'n'},
        {"respect-name", no_argument, NULL, 'f'},
        {"ignore-mode", no_argument, NULL, 'p'},
        {"ignore-owner", no_argument, NULL, 'o'},
        {"ignore-time", no_argument, NULL, 't'},
        {"maximize", no_argument, NULL, 'm'},
        {"minimize", no_argument, NULL, 'M'},
        {"exclude", required_argument, NULL, 'x'},
        {"include", required_argument, NULL, 'i'},
        {NULL, 0, NULL, 0}
    };
#endif

    int opt;

    opts.respect_mode = TRUE;
    opts.respect_owner = TRUE;
    opts.respect_time = TRUE;

    while ((opt = getopt_long(argc, argv, optstr, long_options, NULL)) != -1) {
        switch (opt) {
        case 'p':
            opts.respect_mode = FALSE;
            break;
        case 'o':
            opts.respect_owner = FALSE;
            break;
        case 't':
            opts.respect_time = FALSE;
            break;
        case 'm':
            opts.maximise = TRUE;
            break;
        case 'M':
            opts.minimise = TRUE;
            break;
        case 'f':
            opts.respect_name = TRUE;
            break;
        case 'v':
            opts.verbosity++;
            break;
        case 'c':
            opts.respect_mode = FALSE;
            opts.respect_name = FALSE;
            opts.respect_owner = FALSE;
            opts.respect_time = FALSE;
            break;
        case 'n':
            opts.dry_run = 1;
            break;
        case 'h':
            return help(argv[0]);
        case 'V':
            return version();
        case 'x':
            if (register_regex(&opts.exclude, optarg) != 0)
                return 1;
            break;
        case 'i':
            if (register_regex(&opts.include, optarg) != 0)
                return 1;
            break;
        case '?':
            return 1;
        default:
            jlog(JLOG_ERROR, "Unexpected invalid option: -%c\n", opt);
            return 1;
        }
    }
    return 0;
}
