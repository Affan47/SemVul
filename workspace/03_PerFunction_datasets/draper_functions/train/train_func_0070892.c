sysctl_main(int argc UNUSED_PARAM, char **argv)
{
	int retval;
	int opt;

	opt = getopt32(argv, "+" OPTION_STR);
	argv += optind;
	opt ^= (FLAG_SHOW_KEYS | FLAG_SHOW_KEY_ERRORS);
	option_mask32 = opt;

	if (opt & FLAG_PRELOAD_FILE) {
		option_mask32 |= FLAG_WRITE;

		return sysctl_handle_preload_file(*argv ? *argv : "/etc/sysctl.conf");
	}
	xchdir("/proc/sys");

	if (opt & (FLAG_TABLE_FORMAT | FLAG_SHOW_ALL)) {
		return sysctl_act_recursive(".");
	}

	retval = 0;
	while (*argv) {
		sysctl_dots_to_slashes(*argv);
		retval |= sysctl_act_recursive(*argv);
		argv++;
	}

	return retval;
}
