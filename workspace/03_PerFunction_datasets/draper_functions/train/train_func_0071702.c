parseGetoptValue(int option, const char *optval, optionTable_t *table)
{
	char optstr[] = { '\0', '\0' };

	optstr[0] = (char)option;

	if (optval && !*optval)
		optval = NULL;

	return parseConfigValue(optstr, optval, table, NULL, optstr);
}
