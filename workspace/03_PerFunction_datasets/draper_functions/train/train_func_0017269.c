getopt_argv(char **argv)
{
    int c;

    Cha_optind = 0;
    while ((c = cha_getopt_chasen(argv, stderr)) != EOF) {
	switch (c) {
	case 's':
	    is_partial = 1;
	    break;
	case 'r':
	    cha_set_rcpath(Cha_optarg);
	    break;
	case 'R':
	    cha_set_rcpath("*");
	    break;
	case 'o':
	    output_file = Cha_optarg;
	    break;
	case 'F':


	    if (Cha_optarg[0] == 'h' && Cha_optarg[1] == '\0') {
		opt_form_usage(stdout);
		exit(0);
	    }
	    break;
	case 'V':
	    cha_version(stdout);
	    exit(0);
	case 'h':
	    usage(stdout);
	    exit(0);
	case '?':
	    fprintf(stderr, "Try `%s -h' for more information.\n",
		    CHA_PROG);
	    exit(1);
	}
    }
}
