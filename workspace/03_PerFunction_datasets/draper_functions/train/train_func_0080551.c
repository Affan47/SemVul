thisfield(const char *linebuf, const char *field)
{
	while (lowerconv(*linebuf&0377) == lowerconv(*field&0377)) {
		linebuf++;
		field++;
	}
	if (*field != '\0')
		return NULL;
	while (blankchar(*linebuf&0377))
		linebuf++;
	if (*linebuf++ != ':')
		return NULL;
	while (blankchar(*linebuf&0377))
		linebuf++;
	return (char *)linebuf;
}
