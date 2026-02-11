config_create(char *name, char *options)
{
	Config *config;
	List *tokens;
	int i;

	debug((1, "config_create(name = \"%s\", options = \"%s\")", name, options))

	if (!(config = mem_new(Config)))
		return null;

	if (!(config->name = mem_strdup(name)))
	{
		mem_release(config);
		return null;
	}

	if (!(config->options = list_create(free)))
	{
		mem_release(config->name);
		mem_release(config);
		return null;
	}

	if (!(tokens = split(options, ",")))
	{
		list_release(config->options);
		mem_release(config->name);
		mem_release(config);
		return null;
	}

	for (i = 0; i < list_length(tokens); ++i)
	{
		char *tok = cstr((String *)list_item(tokens, i));
		size_t size = strlen(tok) + 3;
		char *option;

		if (!(option = mem_create(size, char)))
		{
			list_release(tokens);
			list_release(config->options);
			mem_release(config->name);
			mem_release(config);
			return null;
		}

		strlcpy(option, "--", size);
		strlcat(option, tok, size);

		if (!list_append(config->options, option))
		{
			mem_release(option);
			list_release(tokens);
			list_release(config->options);
			mem_release(config->name);
			mem_release(config);
			return null;
		}
	}

	return config;
}
