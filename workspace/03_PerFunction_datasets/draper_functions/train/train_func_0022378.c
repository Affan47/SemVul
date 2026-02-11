emit(FILE *fd, const char *filename, size_t ct)
{
	char buf[BUFSIZ];

	while(ct) {
		size_t len, cc;

		cc = ct > sizeof(buf) ? sizeof(buf) : ct;
		len = fread(buf, 1, cc, fd);

		if (!len)
		       break;

		ct -= len;
		cc = write(STDOUT_FILENO, buf, len);
		if (cc != len)
			err(EXIT_FAILURE, _("write to stdout failed"));
	}

	if (!ct)
		return;
	if (feof(fd))
		errx(EXIT_FAILURE, _("unexpected end of file on %s"), filename);

	err(EXIT_FAILURE, _("failed to read typescript file %s"), filename);
}
