main (int argc, char **argv)
{
	if (argc == 3) {
		if (g_str_equal (argv[1], "-d")) {
			set_warnings ();
			parse_remotes (argv[2]);
			return 0;
		}
	} else {
		usage (argv);
	}

	set_warnings ();

	if (load_subs (argv[1]) == FALSE) {
		g_warning ("Failed to parse %s", argv[1]);
		return 1;
	}

	if (parse_remotes (argv[2]) == FALSE) {
		g_warning ("Failed to work on %s", argv[2]);
		return 1;
	}

	cleanup_subs ();

	return 0;
}
