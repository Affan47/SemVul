handle_skinny_show_lines(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	switch (cmd) {
	case CLI_INIT:
		e->command = "skinny show lines [verbose]";
		e->usage =
			"Usage: skinny show lines\n"
			"       Lists all lines known to the Skinny subsystem.\n"
			"       If 'verbose' is specified, the output includes\n"
			"       information about subs for each line.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc == e->args) {
		if (strcasecmp(a->argv[e->args-1], "verbose")) {
			return CLI_SHOWUSAGE;
		}
	} else if (a->argc != e->args - 1) {
		return CLI_SHOWUSAGE;
	}

	return _skinny_show_lines(a->fd, NULL, NULL, NULL, a->argc, (const char **) a->argv);
}
