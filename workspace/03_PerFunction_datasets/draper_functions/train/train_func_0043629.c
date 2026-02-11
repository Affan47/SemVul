vi_main(int argc, char **argv)
{
	int c;

	INIT_G();

#if ENABLE_FEATURE_VI_USE_SIGNALS || ENABLE_FEATURE_VI_CRASHME
	my_pid = getpid();
#endif
#if ENABLE_FEATURE_VI_CRASHME
	srand((long) my_pid);
#endif
#ifdef NO_SUCH_APPLET_YET

	if (ENABLE_FEATURE_VI_READONLY && applet_name[2]) {
		SET_READONLY_MODE(readonly_mode);
	}
#endif

	vi_setops = VI_AUTOINDENT | VI_SHOWMATCH | VI_IGNORECASE;


#if ENABLE_FEATURE_VI_COLON
	{
		char *p = getenv("EXINIT");
		if (p && *p)
			initial_cmds[0] = xstrndup(p, MAX_INPUT_LEN);
	}
#endif
	while ((c = getopt(argc, argv, "hCRH" IF_FEATURE_VI_COLON("c:"))) != -1) {
		switch (c) {
#if ENABLE_FEATURE_VI_CRASHME
		case 'C':
			crashme = 1;
			break;
#endif
#if ENABLE_FEATURE_VI_READONLY
		case 'R':
			SET_READONLY_MODE(readonly_mode);
			break;
#endif
#if ENABLE_FEATURE_VI_COLON
		case 'c':
			if (*optarg)
				initial_cmds[initial_cmds[0] != 0] = xstrndup(optarg, MAX_INPUT_LEN);
			break;
#endif
		case 'H':
			show_help();

		default:
			bb_show_usage();
			return 1;
		}
	}


	fn_start = optind;
	save_argc = argc;


	while (1) {
		edit_file(argv[optind]);
		if (++optind >= argc)
			break;
	}


	return 0;
}
