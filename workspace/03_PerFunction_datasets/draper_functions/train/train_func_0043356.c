init(int argc, char *argv[])
{
    int c;

    opterr = 0;
    while ((c = getopt(argc, argv, ":o:xstv")) != -1) {
	switch (c) {
	case 'o':
	    outfile = optarg;
	    split(outfile);
	    break;
	case 's':
	    verbose = 1;
	    silent = 1;
	    break;
	case 'v':
	    verbose = 1;
	    break;
	case 't':
	    doTree = 1;
	    break;
	case 'x':
	    external = 1;
	    break;
	case ':':
	    fprintf(stderr, "bcomps: option -%c missing argument - ignored\n", optopt);
	    break;
	case '?':
	    if (optopt == '?')
		usage(0);
	    else
		fprintf(stderr,
			"bcomps: option -%c unrecognized - ignored\n", optopt);
	    break;
	}
    }
    argv += optind;
    argc -= optind;

    if (argc > 0)
	Files = argv;
}
