main(int argc, const char **argv)
{
	const char *cmd;

	cmd = git_extract_argv0_path(argv[0]);
	if (!cmd)
		cmd = "git-help";


	if (!prefixcmp(cmd, "git-")) {
		cmd += 4;
		argv[0] = cmd;
		handle_internal_command(argc, argv);
		die("cannot handle %s internally", cmd);
	}


	argv++;
	argc--;
	handle_options(&argv, &argc, NULL);
	if (argc > 0) {
		if (!prefixcmp(argv[0], "--"))
			argv[0] += 2;
	} else {

		commit_pager_choice();
		printf("usage: %s\n\n", git_usage_string);
		list_common_cmds_help();
		printf("\n%s\n", git_more_info_string);
		exit(1);
	}
	cmd = argv[0];


	setup_path();

	while (1) {
		static int done_help = 0;
		static int was_alias = 0;
		was_alias = run_argv(&argc, &argv);
		if (errno != ENOENT)
			break;
		if (was_alias) {
			fprintf(stderr, "Expansion of alias '%s' failed; "
				"'%s' is not a git command\n",
				cmd, argv[0]);
			exit(1);
		}
		if (!done_help) {
			cmd = argv[0] = help_unknown_cmd(cmd);
			done_help = 1;
		} else
			break;
	}

	fprintf(stderr, "Failed to run command '%s': %s\n",
		cmd, strerror(errno));

	return 1;
}
