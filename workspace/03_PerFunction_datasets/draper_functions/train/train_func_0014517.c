main(int argc, char **argv) {
    int i;
    char *algo;
    int (*func)(int, char **);

    if (argc < 2) {
        usage(argv[0]);
        return -1;
    }

    init_hash_table();

    algo = argv[1];
    for (i = 0; i < strlen(algo); ++i) {
        algo[i] = tolower(algo[i]);
    }

    func = algo_lookup(algo);
    if (func)
        func(argc, argv);
    else
        usage(argv[0]);

    return 0;
}
