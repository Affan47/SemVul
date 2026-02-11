handle_commandnummatches(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	int matches = 0;

	switch (cmd) {
	case CLI_INIT:
		e->command = "_command nummatches";
		e->usage =
			"Usage: _command nummatches \"<line>\" text \n"
			"       This function is used internally to help with command completion and should.\n"
			"       never be called by the user directly.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 4)
		return CLI_SHOWUSAGE;

	matches = ast_cli_generatornummatches(a->argv[2], a->argv[3]);

	ast_cli(a->fd, "%d", matches);

	return CLI_SUCCESS;
}
