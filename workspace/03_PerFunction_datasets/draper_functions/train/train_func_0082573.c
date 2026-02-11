parse_arguments(int argc, char *argv[])
{


	package = strrchr(argv[0], '/');
	if (package == 0)
		package = argv[0];
	else
		package++;

	if (argc==1) {
		just_print_bufsize = 1;
		return;
	}
	if (argc < 2) {
		fprintf(stderr, "usage: %s <bufsize>\n", package);
		exit(9);
	}

    if (strspn (argv[1], "0123456789") != strlen (argv[1])) {
		fprintf(stderr, "usage: %s <bufsize>\n", package);
		exit(8);
    }

	nframes = strtoul(argv[1], NULL, 0);
	if (errno == ERANGE) {
		fprintf(stderr, "%s: invalid buffer size: %s (range is 1-8192)\n",
			package, argv[1]);
		exit(2);
	}

    if (nframes < 1 || nframes > 8182) {
		fprintf(stderr, "%s: invalid buffer size: %s (range is 1-8192)\n",
			package, argv[1]);
		exit(3);
    }
}
