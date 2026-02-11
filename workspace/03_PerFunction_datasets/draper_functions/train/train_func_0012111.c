cmd_help(char **arg)
{
	const char *topic = get_arg(arg);

	if (topic) {
		struct cmddb_record cmd;
		struct opdb_key key;

		if (!cmddb_get(topic, &cmd)) {
			printc("\x1b[1mCOMMAND: %s\x1b[0m\n\n%s\n",
			       cmd.name, cmd.help);
			return 0;
		}

		if (!opdb_get(topic, &key, NULL)) {
			printc("\x1b[1mOPTION: %s (%s)\x1b[0m\n\n%s\n",
			       key.name, type_text(key.type), key.help);
			return 0;
		}

		printc_err("help: unknown command: %s\n", topic);
		return -1;
	} else {
		struct vector v;

		vector_init(&v, sizeof(const char *));

		if (!cmddb_enum(push_command_name, &v)) {
			printc("Available commands:\n");
			namelist_print(&v);
			printc("\n");
		} else {
			pr_error("help: can't allocate memory for command list");
		}

		vector_realloc(&v, 0);

		if (!opdb_enum(push_option_name, &v)) {
			printc("Available options:\n");
			namelist_print(&v);
			printc("\n");
		} else {
			pr_error("help: can't allocate memory for option list");
		}

		vector_destroy(&v);

		printc("Type \"help <topic>\" for more information.\n");
		printc("Press Ctrl+D to quit.\n");
	}

	return 0;
}
