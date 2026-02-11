fix_line_ending(char *line)
{
	unsigned int len = strlen(line);
	if (len > 2 && line[len - 2] == '\r') {
		line[len - 2] = '\n';
		line[len - 1] = '\0';
	}
}
