get_config_option(char *ptr, char **arg)
{
	int i;

	for (i = 0; options_list[i].name; i++) {
		if (!strncasecmp(ptr, options_list[i].name, strlen(options_list[i].name))) {

			ptr += strlen(options_list[i].name);


			while (*ptr == '=' || *ptr == ' ' || *ptr == '\t')
				ptr++;

			*arg = ptr;
			return options_list[i].option;
		}
	}

	*arg = ptr;
	return 0;
}
