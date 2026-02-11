handle_skinny_show_devices(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{

	switch (cmd) {
	case CLI_INIT:
		e->command = "skinny show devices";
		e->usage =
			"Usage: skinny show devices\n"
			"       Lists all devices known to the Skinny subsystem.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	return _skinny_show_devices(a->fd, NULL, NULL, NULL, a->argc, (const char **) a->argv);
}
