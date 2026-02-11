_opt_args(int argc, char **argv)
{
	char **rest = NULL;
	int leftover;

	set_options(argc, argv);

	leftover = 0;
	if (optind < argc) {
		rest = argv + optind;
		while (rest[leftover] != NULL)
			leftover++;
	}
	if (leftover != 1) {
		error("too many parameters");
		_usage();
		exit(error_exit);
	}

	_parse_jobid_stepid(*(argv + optind));

	if (!_opt_verify())
		exit(error_exit);
}
