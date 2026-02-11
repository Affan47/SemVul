do_args(int argc, char *argv[])
{
    int ch;
    char *option_strings;
    extern int optind;

#if !defined( ORIGINAL )
    option_strings = "sr";
#else
    option_strings = "s";
#endif

    while ((ch = getopt(argc, argv, option_strings)) != EOF) {
	switch (ch) {
	case 's':
	    score_only = 1;
	    break;
#if !defined( ORIGINAL )
	case 'r':
	    do_restore = 1;
	    break;
#endif
	case '?':
	default:
	    usage();
	    break;
	}
    }

    argc -= optind;
    argv += optind;
    if (argc >= 3 || argc == 0) {
	usage();
	return;
    }

    if (read_mesg(argv[0])) {
	exit(1);
    }
#if !defined( ORIGINAL )
    if (argc == 2) {
	rest_file = argv[1];
    }
#endif

}
