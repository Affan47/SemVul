parse_cmdline(int argc, char *argv[], struct parameters *p)
{
	struct option long_options[] = {
		{ "help",         0, NULL, 'h' },
		{ "about",        0, NULL, 'a' },
		{ "fifo-path",    1, NULL, 'f' },
		{ 0, 0, 0, 0 }
	};

	int val, opt_index = 0, arg;

	while ((val = getopt_long(argc, argv, "haf:",
					long_options, &opt_index)) != -1) {

		switch (val) {
			case 'h':
				show_help(argv[0]);
				exit(0);

			case 'a':
				show_about();
				exit(0);

			case 'f':
				p->fifo_path = optarg;
				break;

			default:
				show_help(argv[0]);
				exit(-1);
		}
	}

	if (*(argv + optind) == NULL) {
		show_help(argv[0]);
		exit(-1);
	}

	p->message = *(argv + optind);
}
