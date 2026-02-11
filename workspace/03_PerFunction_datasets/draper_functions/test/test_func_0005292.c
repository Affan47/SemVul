set_option(char *opt, char *value)
{
	const char *argv[SIZEOF_ARG];
	int valuelen;
	int argc = 0;


	while (argc < ARRAY_SIZE(argv) && (valuelen = strcspn(value, " \t"))) {
		argv[argc++] = value;
		value += valuelen;


		if (!*value || argc >= ARRAY_SIZE(argv))
			break;

		*value++ = 0;
		while (isspace(*value))
			value++;
	}

	if (!strcmp(opt, "color"))
		return option_color_command(argc, argv);

	if (!strcmp(opt, "set"))
		return option_set_command(argc, argv);

	if (!strcmp(opt, "bind"))
		return option_bind_command(argc, argv);

	config_msg = "Unknown option command";
	return ERR;
}
