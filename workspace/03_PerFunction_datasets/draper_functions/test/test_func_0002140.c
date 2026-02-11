main(int argc, char **argv)
{
	gfarm_error_t e;
	int i, c, status = 0;
	extern int optind;

	if (argc > 0)
		program_name = basename(argv[0]);
	e = gfarm_initialize(&argc, &argv);
	if (e != GFARM_ERR_NO_ERROR) {
		fprintf(stderr, "%s: %s\n", program_name,
		    gfarm_error_string(e));
		exit(1);
	}

	while ((c = getopt(argc, argv, "h?")) != -1) {
		switch (c) {
		case 'h':
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc <= 0)
		usage();

	for (i = 0; i < argc; i++) {
		e = gfs_rmdir(argv[i]);
		if (e != GFARM_ERR_NO_ERROR) {
			fprintf(stderr, "%s: %s: %s\n",
			    program_name, argv[i], gfarm_error_string(e));
			status = 1;
		}
	}
	e = gfarm_terminate();
	if (e != GFARM_ERR_NO_ERROR) {
		fprintf(stderr, "%s: %s\n", program_name,
		    gfarm_error_string(e));
		status = 1;
	}
	return (status);
}
