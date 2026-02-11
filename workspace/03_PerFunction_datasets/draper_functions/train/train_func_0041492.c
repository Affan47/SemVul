handle_orig(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	static const char * const choices[] = { "application", "extension", NULL };
	char *res = NULL;
	switch (cmd) {
	case CLI_INIT:
		e->command = "channel originate";
		e->usage =
			"  There are two ways to use this command. A call can be originated between a\n"
			"channel and a specific application, or between a channel and an extension in\n"
			"the dialplan. This is similar to call files or the manager originate action.\n"
			"Calls originated with this command are given a timeout of 30 seconds.\n\n"

			"Usage1: channel originate <tech/data> application <appname> [appdata]\n"
			"  This will originate a call between the specified channel tech/data and the\n"
			"given application. Arguments to the application are optional. If the given\n"
			"arguments to the application include spaces, all of the arguments to the\n"
			"application need to be placed in quotation marks.\n\n"

			"Usage2: channel originate <tech/data> extension [exten@][context]\n"
			"  This will originate a call between the specified channel tech/data and the\n"
			"given extension. If no context is specified, the 'default' context will be\n"
			"used. If no extension is given, the 's' extension will be used.\n";
		return NULL;
	case CLI_GENERATE:

		ast_module_ref(ast_module_info->self);
		if (a->pos == 3) {
			res = ast_cli_complete(a->word, choices, a->n);
		} else if (a->pos == 4) {
			if (!strcasecmp("application", a->argv[3])) {
				res = ast_complete_applications(a->line, a->word, a->n);
			}
		}
		ast_module_unref(ast_module_info->self);
		return res;
	}

	if (ast_strlen_zero(a->argv[2]) || ast_strlen_zero(a->argv[3]))
		return CLI_SHOWUSAGE;


	ast_module_ref(ast_module_info->self);

	if (!strcasecmp("application", a->argv[3])) {
		res = orig_app(a->fd, a->argv[2], a->argv[4], a->argv[5]);
	} else if (!strcasecmp("extension", a->argv[3])) {
		res = orig_exten(a->fd, a->argv[2], a->argv[4]);
	} else {
		res = CLI_SHOWUSAGE;
	}

	ast_module_unref(ast_module_info->self);

	return res;
}
