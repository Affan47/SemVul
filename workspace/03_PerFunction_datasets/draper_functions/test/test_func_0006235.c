init(int argc, char *argv[])
{
    unsigned int c;

    opterr = 0;
    while ((c = getopt(argc, argv, "necCaDUrsv")) != -1) {
	switch (c) {
	case 'e':
	    flags |= EDGES;
	    break;
	case 'n':
	    flags |= NODES;
	    break;
	case 'c':
	    flags |= CC;
	    break;
	case 'C':
	    flags |= CL;
	    tot_cl = 0;
	    break;
	case 'a':
	    flags = NODES | EDGES | CC | CL;
	    break;
	case 'r':
	    recurse = 1;
	    break;
	case 's':
	    silent = 1;
	    break;
	case 'v':
	    verbose = 1;
	    break;
	case 'D':
	    gtype = DIRECTED;
	    break;
	case 'U':
	    gtype = UNDIRECTED;
	    break;
	case '?':
	    if (optopt == '?')
		usage(0);
	    else
		fprintf(stderr, "gc: option -%c unrecognized - ignored\n",
			optopt);
	    break;
	}
    }
    argv += optind;
    argc -= optind;

    if (argc)
	Files = argv;
    if (flags == 0)
	flags = NODES | EDGES;
    if (gtype == 0)
	gtype = DIRECTED | UNDIRECTED;
    outfile = stdout;
}
