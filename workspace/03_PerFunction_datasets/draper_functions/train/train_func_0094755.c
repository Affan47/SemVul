help_unknown_cmd(const char *cmd)
{
	int i, n, best_similarity = 0;
	struct cmdnames main_cmds, other_cmds;

	memset(&main_cmds, 0, sizeof(main_cmds));
	memset(&other_cmds, 0, sizeof(main_cmds));
	memset(&aliases, 0, sizeof(aliases));

	git_config(git_unknown_cmd_config, NULL);

	load_command_list("git-", &main_cmds, &other_cmds);

	add_cmd_list(&main_cmds, &aliases);
	add_cmd_list(&main_cmds, &other_cmds);
	qsort(main_cmds.names, main_cmds.cnt,
	      sizeof(main_cmds.names), cmdname_compare);
	uniq(&main_cmds);


	for (i = 0; i < main_cmds.cnt; ++i)
		main_cmds.names[i]->len =
			levenshtein(cmd, main_cmds.names[i]->name, 0, 2, 1, 4);

	qsort(main_cmds.names, main_cmds.cnt,
	      sizeof(*main_cmds.names), levenshtein_compare);

	if (!main_cmds.cnt)
		die ("Uh oh. Your system reports no Git commands at all.");

	best_similarity = main_cmds.names[0]->len;
	n = 1;
	while (n < main_cmds.cnt && best_similarity == main_cmds.names[n]->len)
		++n;
	if (autocorrect && n == 1) {
		const char *assumed = main_cmds.names[0]->name;
		main_cmds.names[0] = NULL;
		clean_cmdnames(&main_cmds);
		fprintf(stderr, "WARNING: You called a Git program named '%s', "
			"which does not exist.\n"
			"Continuing under the assumption that you meant '%s'\n",
			cmd, assumed);
		if (autocorrect > 0) {
			fprintf(stderr, "in %0.1f seconds automatically...\n",
				(float)autocorrect/10.0);
			poll(NULL, 0, autocorrect * 100);
		}
		return assumed;
	}

	fprintf(stderr, "git: '%s' is not a git-command. See 'git --help'.\n", cmd);

	if (best_similarity < 6) {
		fprintf(stderr, "\nDid you mean %s?\n",
			n < 2 ? "this": "one of these");

		for (i = 0; i < n; i++)
			fprintf(stderr, "\t%s\n", main_cmds.names[i]->name);
	}

	exit(1);
}
