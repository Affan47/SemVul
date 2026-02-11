handle_set_extenpatternmatchnew(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	int oldval = 0;

	switch (cmd) {
	case CLI_INIT:
		e->command = "dialplan set extenpatternmatchnew true";
		e->usage =
			"Usage: dialplan set extenpatternmatchnew true|false\n"
			"       Use the NEW extension pattern matching algorithm, true or false.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 4)
		return CLI_SHOWUSAGE;

	oldval =  pbx_set_extenpatternmatchnew(1);

	if (oldval)
		ast_cli(a->fd, "\n    -- Still using the NEW pattern match algorithm for extension names in the dialplan.\n");
	else
		ast_cli(a->fd, "\n    -- Switched to using the NEW pattern match algorithm for extension names in the dialplan.\n");

	return CLI_SUCCESS;
}
