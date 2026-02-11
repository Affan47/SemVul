main(int argc, const char *const argv[])
{
    clock_t time_taken = clock();
    int i;
    int rv;
    int list_provided = 0;
    tst_suite *suite = NULL;
    sub_suite *subsuite;

    setprogname("Ferret Test");

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-v")) {
            verbose = true;
            continue;
        }
        if (!strcmp(argv[i], "-x")) {
            exclude = true;
            continue;
        }
        if (!strcmp(argv[i], "-l")) {
            list_tests = true;
            continue;
        }
        if (!strcmp(argv[i], "-f")) {
            force = true;
            continue;
        }
        if (!strcmp(argv[i], "-q")) {
            quiet = true;
            continue;
        }
        if (argv[i][0] == '-') {
            fprintf(stderr, USAGE, argv[i]);
            exit(1);
        }
        list_provided = 1;
    }

    if (list_provided) {


        testlist = calloc(argc + 1, sizeof(char *));
        for (i = 1; i < argc; i++) {
            testlist[i - 1] = (char *) argv[i];
        }
    }

    for (i = 0; i < (int)NELEMS(all_tests); i++) {
        suite = all_tests[i].func(suite);
    }


    rv = report(suite);
    printf("Finished in %0.3f seconds\n",
           (double) (clock() - time_taken) / CLOCKS_PER_SEC);


    while ((subsuite = suite->head) != NULL) {
        suite->head = subsuite->next;
        free(subsuite->name);
        free(subsuite);
    }
    free(suite);
    free(testlist);
    do_clean_up();

    return rv;
}
