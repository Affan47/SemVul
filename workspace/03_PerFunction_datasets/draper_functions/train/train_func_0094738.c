set_options(char *argv[]) {
	int ch;
	int argc;

	argc = 1;
	while (argv[argc] != '\0') {
		if (argv[argc][0] == '-') argc++;
		else break;
	}

	if (argv[argc] == '\0')
		usage();

	while ((ch = getopt(argc, argv, "r")) != -1) {
		switch (ch) {
		case 'r':
			restart_mode = 1;
			break;
		}
	}
	return optind;
}
