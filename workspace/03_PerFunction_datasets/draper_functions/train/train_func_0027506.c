xmlnode_file_borked(char *file)
{
	XML_Parser p;
	char buf[BUFSIZ];
	static char err[1024];
	int fd, len, done;

	if (NULL == file)
		return "no file specified";

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return "unable to open file";

	p = XML_ParserCreate(NULL);
	while (1) {
		len = read(fd, buf, BUFSIZ);
		done = len < BUFSIZ;
		if (!XML_Parse(p, buf, len, done)) {
			snprintf(err, 1023, "%s at line %d and column %d",
				XML_ErrorString(XML_GetErrorCode(p)),
				XML_GetErrorLineNumber(p),
				XML_GetErrorColumnNumber(p));
			XML_ParserFree(p);
			close(fd);
			return err;
		}
	}
}
