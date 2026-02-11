main(int argc, char **argv)
{
	int c;
	register cmd *act;
	extern int optind;
	extern char *optarg;


	vmm_init();
	halloc_init(FALSE);

	progname = argv[0];

	while ((c = getopt(argc, argv, "R")) != EOF)
		switch (c) {
		case 'R':
			rflag++;
			break;

		default:
			oops("usage: %s", usage);
			break;
		}

	if ((argc -= optind) < 2)
		oops("usage: %s", usage);

	if ((act = parse(argv[optind])) == NULL)
		badk(argv[optind]);
	optind++;
	doit(act, argv[optind]);
	return 0;
}
