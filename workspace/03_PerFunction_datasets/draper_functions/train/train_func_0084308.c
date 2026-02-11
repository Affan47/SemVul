count_lines_in_buf(PQExpBuffer buf)
{
	int			lineno = 0;
	const char *lines = buf->data;

	while (*lines != '\0')
	{
		lineno++;

		lines = strchr(lines, '\n');
		if (!lines)
			break;
		lines++;
	}

	return lineno;
}
