do_dictionary(int argc, char *argv[])
{
    const char *dict_filename = NULL;
    const char *zip_filename = NULL;
    int err;

    for (;;) {
        int c;
        int idx;
        c = getopt_long(argc, argv, short_opts, long_opts, &idx);
        if (c == -1)
            break;
        switch (c) {
        case 'd':
            dict_filename = optarg;
            break;
        case 'h':
            print_help(basename(argv[0]));
            return EXIT_SUCCESS;
        default:
            yazc_err("unexpected getopt_long() value '%c'.\n", c);
            return EXIT_FAILURE;
        }
    }

    if (optind >= argc) {
        yazc_err("missing filename.\n");
        return EXIT_FAILURE;
    }

    zip_filename = argv[optind];

    printf("Dictionary file: %s\n", !dict_filename ? "stdin" : dict_filename);
    printf("Filename: %s\n", zip_filename);

    if (zc_new(&ctx)) {
        yazc_err("zc_new() failed!\n");
        return EXIT_FAILURE;
    }

    err = launch_crack(dict_filename, zip_filename);

    zc_unref(ctx);

    return err;
}
