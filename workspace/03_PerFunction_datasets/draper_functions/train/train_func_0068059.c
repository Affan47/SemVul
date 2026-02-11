main (int argc, char *argv[]) {
	if (argc < 2)
		usage();

	opta = optc = optl = optL = optx = 0;

	if (argc == 2)
		optl = 1;
	else
	while(1) {
	    switch(getopt(argc, argv, "alLc")) {
	      case 'a':
		opta = 1;
		continue;
	      case 'c':
		optc = 1;
		continue;
	      case 'L':
		optL = 1;
		continue;
	      case 'l':
		optl = 1;
		continue;
	      case '?':
	      default:
		usage();
	      case -1:
		break;
	    }
	    break;
        }

	if (optind < argc) {
	    if ((in = fopen(argv[optind], "r")) == NULL) {
		printf("\nUnable to open file %s.\n", argv[optind]);
		exit(0);
	    }
	    optind++;
        } else
	    usage();

	if (optind != argc) {
	    if (optind != argc-1 || opta)
	      usage();
	    codepage = atoi(argv[optind]);
	    optx = 1;
	}

	if (optc)
	  handle_codepage(0);
	else
	  handle_fontfile();

	if (optx) {
	    printf("no page %d found\n", codepage);
	    exit(1);
	}

	fclose(in);
	return (0);
}
