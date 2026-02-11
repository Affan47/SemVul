parser_check_configitem(char *line, char *config)
{
	int len;

	len = strlen(config);
	if (!strncasecmp(line, config, len)) {
		return line + len;
	}
	return NULL;
}
