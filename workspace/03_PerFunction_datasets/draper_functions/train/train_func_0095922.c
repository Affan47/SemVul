inline_undotify(char *buf, size_t len)
{
	unsigned pos;
	unsigned dots;
	char *reader, *writer;

	writer = buf;
	reader = writer;

	pos = 0;
	dots = 0;

	while (pos < len) {
		if (*reader == '.') {
			reader++;
			pos++;
			dots++;
			continue;
		}
		*writer++ = *reader++;
		pos++;
	}


	return len - dots;
}
