initargs(int argc, char **argv)
{
    int c;

    CmdName = cmdName(argv[0]);
    opterr = 0;
    while ((c = getopt(argc, argv, ":gdo:")) != -1) {
	switch (c) {
	case 'd':
	    act = ToGV;
	    break;
	case 'g':
	    act = ToGXL;
	    break;
	case 'o':
	    outFile = openFile(optarg, "w");
	    break;
	case ':':
	    fprintf(stderr, "%s: option -%c missing argument\n", CmdName, optopt);
	    break;
	case '?':
	    if (optopt == '?')
		usage(0);
	    else {
		fprintf(stderr, "%s: option -%c unrecognized\n", CmdName,
			optopt);
		exit(1);
	    }
	}
    }

    argv += optind;
    argc -= optind;

    if (argc > 0)
	Files = argv;
    if (!outFile)
	outFile = stdout;
    if (act == Unset)
	setAction();
}
