handle_cli_dialplan_remove_context(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	struct ast_context *con;

	switch (cmd) {
	case CLI_INIT:
		e->command = "dialplan remove context";
		e->usage =
			"Usage: dialplan remove context <context>\n"
			"       Removes all extensions from a specified context.\n";
		return NULL;
	case CLI_GENERATE:
		return complete_dialplan_remove_context(a);
	}

	if (a->argc != 4) {
		return CLI_SHOWUSAGE;
	}

	con = ast_context_find(a->argv[3]);

	if (!con) {
		ast_cli(a->fd, "There is no such context as '%s'\n",
                        a->argv[3]);
                return CLI_SUCCESS;
	} else {
		ast_context_destroy(con, registrar);
		ast_cli(a->fd, "Removing context '%s'\n",
			a->argv[3]);
		return CLI_SUCCESS;
	}
}
