main(int argc, char **argv)
{
    Octstr *filename = NULL;
    unsigned long num = 1, j;
    int opt;
    Octstr *mime, *mime2;
    MIMEEntity *m;

    gwlib_init();

    while ((opt = getopt(argc, argv, "hv:n:")) != EOF) {
        switch (opt) {
            case 'v':
                log_set_output_level(atoi(optarg));
                break;
            case 'n':
                num = atoi(optarg);
                break;
            case '?':
            default:
                error(0, "Invalid option %c", opt);
                help();
                panic(0, "Stopping.");
        }
    }

    if (optind == argc) {
        help();
        exit(0);
    }

    filename = octstr_create(argv[argc-1]);
    mime = octstr_read_file(octstr_get_cstr(filename));

    for (j = 1; j <= num; j++) {

    info(0,"MIME Octstr from file `%s':", octstr_get_cstr(filename));
    octstr_dump(mime, 0);

    m = mime_octstr_to_entity(mime);

    mime_entity_dump(m);

    mime2 = mime_entity_to_octstr(m);

    info(0, "MIME Octstr after reconstruction:");
    octstr_dump(mime2, 0);

    if (octstr_compare(mime, mime2) != 0) {
        error(0, "MIME content from file `%s' and reconstruction differs!",
              octstr_get_cstr(filename));
    } else {
        info(0, "MIME Octstr compare result has been successfull.");
    }

    octstr_destroy(mime2);
    mime_entity_destroy(m);

    }

    octstr_destroy(filename);

    gwlib_shutdown();

    return 0;
}
