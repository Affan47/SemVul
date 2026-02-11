open_tmpfile(void)
{
	char *cp;
	char path[MAXPATHLEN];
	int fd;

	cp = getenv("TMPDIR");
	if (cp == NULL)
		cp = "/tmp";
	snprintf(path, sizeof(path), "%s/epkg-XXXXXX", cp);

	fd = mkstemp(path);
	if (fd == -1)
	{
		fprintf(stderr, "  ! cannot open temp file: "
			"mkstemp(\"%s\"): %s\n",
			path, strerror(errno));
		return -1;
	}

	unlink(path);

	return fd;
}
