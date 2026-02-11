parse_command(const char *line)
{
	char *command;

	debug("Parsing monitoring command");

	line = skip_whitespace(line);
	if (line[0] == '[')
		command = xstrdup(line);
	else
		xasprintf(&command, "[%lu] %s", (unsigned long)time(NULL),
		    line);

	return command;
}
