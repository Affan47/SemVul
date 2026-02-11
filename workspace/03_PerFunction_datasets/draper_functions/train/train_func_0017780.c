command_register(command_t command)
{
	int i;

	if (registered == MAX_COMMANDS)
	{
		fprintf(stderr, "unable to register command, please increase "
				"MAX_COMMANDS\n");
		return;
	}

	cmds[registered] = command;

	if (!active)
	{
		for (i = 0; i < countof(cmds[registered].options) - 1; i++)
		{
			if (!cmds[registered].options[i].name)
			{
				break;
			}
		}
		if (i > countof(cmds[registered].options) - 3)
		{
			fprintf(stderr, "command '%s' registered too many options, please "
					"increase MAX_OPTIONS\n", command.cmd);
		}
		else
		{
			cmds[registered].options[i++] = (command_option_t) {
				"debug",	'v', 1, "set debug level, default: 1"
			};
			cmds[registered].options[i++] = (command_option_t) {
				"options",	'+', 1, "read command line options from file"
			};
		}
	}
	registered++;
}
