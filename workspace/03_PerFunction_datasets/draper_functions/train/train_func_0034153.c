directive(line)
	char *line;
{
	return (line == curline && *line == '%');
}
