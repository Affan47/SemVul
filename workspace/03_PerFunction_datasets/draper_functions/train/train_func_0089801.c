prependDirectory(ArchiveHandle *AH, const char *relativeFilename)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	static char buf[MAXPGPATH];
	char	   *dname;

	dname = ctx->directory;

	if (strlen(dname) + 1 + strlen(relativeFilename) + 1 > MAXPGPATH)
		die_horribly(AH, modulename, "path name too long: %s", dname);

	strcpy(buf, dname);
	strcat(buf, "/");
	strcat(buf, relativeFilename);

	return buf;
}
