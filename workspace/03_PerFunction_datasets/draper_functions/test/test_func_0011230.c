rm_main(int argc UNUSED_PARAM, char **argv)
{
	int status = 0;
	int flags = 0;
	unsigned opt;

	opt_complementary = "f-i:i-f";

	opt = getopt32(argv, "fiRrv");
	argv += optind;
	if (opt & 1)
		flags |= FILEUTILS_FORCE;
	if (opt & 2)
		flags |= FILEUTILS_INTERACTIVE;
	if (opt & (8|4))
		flags |= FILEUTILS_RECUR;

	if (*argv != NULL) {
		do {
			const char *base = bb_get_last_path_component_strip(*argv);

			if (DOT_OR_DOTDOT(base)) {
				bb_error_msg("can't remove '.' or '..'");
			} else if (remove_file(*argv, flags) >= 0) {
				continue;
			}
			status = 1;
		} while (*++argv);
	} else if (!(flags & FILEUTILS_FORCE)) {
		bb_show_usage();
	}

	return status;
}
