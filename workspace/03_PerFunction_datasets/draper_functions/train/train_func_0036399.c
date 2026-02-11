getUntil(memBuf_t *mp, int until)
{
	static char *buf = NULL;
	static size_t bufsize = 0;
	size_t count = 0;
	int c;

	log(("\n\ngetUntil('%c')\n\n", until));

	while ((c = memGetc(mp)) != EOF) {
		if (options.debug)
			logChar(c);
		if ((char)c == until) {
			term(buf, bufsize, count);
			if (options.debug)
				logChar(EOF);
			return buf;
		}
		addchar(buf, bufsize, count, (char)c);
	}
	if (options.debug)
		logChar(EOF);
	return NULL;
}
