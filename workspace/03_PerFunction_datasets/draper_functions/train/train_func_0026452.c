parse_args(int argc, char **argv)
{
	int opt;
	struct option long_opts[] = {
		{"debug", no_argument, 0, 'd'},
		{"help", no_argument, 0, 'h'},
		{"profile", required_argument, 0, 'p'},
		{"namespace", required_argument, 0, 'n'},
		{"immediate", no_argument, 0, 'i'},
		{"verbose", no_argument, 0, 'v'},
	};

	while ((opt = getopt_long(argc, argv, "+dhp:n:iv", long_opts, NULL)) != -1) {
		switch (opt) {
		case 'd':
			opt_debug = true;
			break;
		case 'h':
			usage(argv[0], false);
			break;
		case 'p':
			opt_profile = optarg;
			break;
		case 'n':
			opt_namespace = optarg;
			break;
		case 'i':
			opt_immediate = true;
			break;
		case 'v':
			opt_verbose = true;
			break;
		default:
			usage(argv[0], true);
			break;
		}
	}

	if (optind >= argc)
		usage(argv[0], true);

	return argv + optind;
}
