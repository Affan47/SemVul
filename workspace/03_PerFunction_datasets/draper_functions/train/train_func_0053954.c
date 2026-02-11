alias_show(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
#define FORMAT "%-50.50s %-50.50s\n"
	struct cli_alias *alias;
	struct ao2_iterator i;

	switch (cmd) {
	case CLI_INIT:
		e->command = "cli show aliases";
		e->usage =
			"Usage: cli show aliases\n"
			"       Displays a list of aliased CLI commands.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	ast_cli(a->fd, FORMAT, "Alias Command", "Real Command");

	i = ao2_iterator_init(cli_aliases, 0);
	for (; (alias = ao2_iterator_next(&i)); ao2_ref(alias, -1)) {
		ast_cli(a->fd, FORMAT, alias->alias, alias->real_cmd);
	}
	ao2_iterator_destroy(&i);

	return CLI_SUCCESS;
#undef FORMAT
}
