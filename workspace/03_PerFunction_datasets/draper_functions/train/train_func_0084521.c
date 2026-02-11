getfield (char *newline)

{
	static char *line = NULL;
	char *end, *field;

	if (newline)
		line = newline;

	if (!line)
		return (NULL);

	field = line;
#ifdef IPV6CONF

	if ((end = strchr(line, '|')) == NULL)
#else

	if ((end = strchr(line, ':')) == NULL)
#endif

	{
		line = NULL;
		if ((end = strchr(field, '\n')) == NULL)
			end = field + strlen(field);
	}
	else
		line = end + 1;

	*end = '\0';
	if (strlen(field))
		return (field);
	else
		return (NULL);
}
