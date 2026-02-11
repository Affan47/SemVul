main(int argc, char **argv) {
    int opt;
    struct augeas *aug;
    char *loadpath = NULL;
    size_t loadpathlen = 0;
    enum {
        VAL_NO_STDINC = CHAR_MAX + 1,
        VAL_NO_TYPECHECK = VAL_NO_STDINC + 1,
        VAL_VERSION = VAL_NO_TYPECHECK + 1
    };
    struct option options[] = {
        { "help",      0, 0, 'h' },
        { "include",   1, 0, 'I' },
        { "trace",     0, 0, 't' },
        { "nostdinc",  0, 0, VAL_NO_STDINC },
        { "notypecheck",  0, 0, VAL_NO_TYPECHECK },
        { "version",  0, 0, VAL_VERSION },
        { 0, 0, 0, 0}
    };
    int idx;
    unsigned int flags = AUG_TYPE_CHECK|AUG_NO_MODL_AUTOLOAD;
    progname = argv[0];

    setlocale(LC_ALL, "");
    while ((opt = getopt_long(argc, argv, "hI:t", options, &idx)) != -1) {
        switch(opt) {
        case 'I':
            argz_add(&loadpath, &loadpathlen, optarg);
            break;
        case 't':
            flags |= AUG_TRACE_MODULE_LOADING;
            break;
        case 'h':
            usage();
            break;
        case VAL_NO_STDINC:
            flags |= AUG_NO_STDINC;
            break;
        case VAL_NO_TYPECHECK:
            flags &= ~(AUG_TYPE_CHECK);
            break;
        case VAL_VERSION:
            print_version = true;
            break;
        default:
            usage();
            break;
        }
    }

    if (!print_version && optind >= argc) {
        fprintf(stderr, "Expected .aug file\n");
        usage();
    }

    argz_stringify(loadpath, loadpathlen, PATH_SEP_CHAR);
    aug = aug_init(NULL, loadpath, flags);
    if (aug == NULL) {
        fprintf(stderr, "Memory exhausted\n");
        return 2;
    }

    if (print_version) {
        print_version_info(aug);
        return EXIT_SUCCESS;
    }

    if (__aug_load_module_file(aug, argv[optind]) == -1) {
        fprintf(stderr, "%s\n", aug_error_message(aug));
        const char *s = aug_error_details(aug);
        if (s != NULL) {
            fprintf(stderr, "%s\n", s);
        }
        exit(EXIT_FAILURE);
    }

    aug_close(aug);
    free(loadpath);
}
