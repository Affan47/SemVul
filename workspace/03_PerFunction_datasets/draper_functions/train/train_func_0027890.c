main(int argc, char *argv[])
{
	int c, f;
	struct stat sb;

	f = 0;
	do {
		c = getopt(argc, argv, "f");
		if (c == EOF)
			break;

		switch (c) {

		case 'f':
			f = 1;
			break;
		case '?':
			fprintf(stderr, "%s: invalid option -%c\n",
				argv[0], optopt);
			return 1;
		}

	} while (1);


	if (argc - optind < 2) {
		fprintf(stderr, "Usage: %s [-f] source dest\n", argv[0]);
		return 1;
	}


	memset(&sb, 0, sizeof(struct stat));
	if (stat(argv[argc - 1], &sb) < 0 && argc - optind > 2) {
		if (!(S_ISDIR(sb.st_mode))) {
			fprintf(stderr,
				"multiple targets and %s is not a directory\n",
				argv[argc - 1]);
			return 1;
		}
	}


	if (f)
		nuke(argv[argc - 1]);


	for (c = optind; c < argc - 1; c++)
		if (copy(argv[c], argv[argc - 1]) < 0) {
			perror("Could not copy file");
			return -1;
		}


	for (c = optind; c < argc - 1; c++)
		if (nuke(argv[c]) < 0) {
			perror("Could not rm file");
			return -1;
		}
	return 0;
}
