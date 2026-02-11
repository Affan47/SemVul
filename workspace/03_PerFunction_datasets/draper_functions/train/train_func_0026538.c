readlink_main(int argc UNUSED_PARAM, char **argv)
{
	char *buf;
	char *fname;

	IF_FEATURE_READLINK_FOLLOW(
		unsigned opt;

		opt_complementary = "=1";
		opt = getopt32(argv, "fnvsq");
		fname = argv[optind];
	)
	IF_NOT_FEATURE_READLINK_FOLLOW(
		const unsigned opt = 0;
		if (argc != 2) bb_show_usage();
		fname = argv[1];
	)


	if (!(opt & 4))
		logmode = LOGMODE_NONE;

	if (opt & 1) {
		buf = xmalloc_realpath(fname);
	} else {
		buf = xmalloc_readlink_or_warn(fname);
	}

	if (!buf)
		return EXIT_FAILURE;
	printf((opt & 2) ? "%s" : "%s\n", buf);

	if (ENABLE_FEATURE_CLEAN_UP)
		free(buf);

	fflush_stdout_and_exit(EXIT_SUCCESS);
}
