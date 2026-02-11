handle_cli_agi_debug(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	switch (cmd) {
	case CLI_INIT:
		e->command = "agi set debug [on|off]";
		e->usage =
			"Usage: agi set debug [on|off]\n"
			"       Enables/disables dumping of AGI transactions for\n"
			"       debugging purposes.\n";
		return NULL;

	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != e->args)
		return CLI_SHOWUSAGE;

	if (strncasecmp(a->argv[3], "off", 3) == 0) {
		agidebug = 0;
	} else if (strncasecmp(a->argv[3], "on", 2) == 0) {
		agidebug = 1;
	} else {
		return CLI_SHOWUSAGE;
	}
	ast_cli(a->fd, "AGI Debugging %sabled\n", agidebug ? "En" : "Dis");
	return CLI_SUCCESS;
}
