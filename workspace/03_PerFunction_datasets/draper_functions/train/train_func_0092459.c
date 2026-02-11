maildir_names(const char *maildir, char **newdir, char **curdir, char **tmpdir)
{
	int len = strlen(maildir) + strlen(MAILDIR_NEW) + 2;

	if (maildir == NULL || strlen(maildir) <= 0)
		return -1;
	if (newdir != NULL) {
		MALLOC(*newdir, len);
		snprintf(*newdir, len, "%s/%s", maildir, MAILDIR_NEW);
	}
	if (curdir != NULL) {
		MALLOC(*curdir, len);
		snprintf(*curdir, len, "%s/%s", maildir, MAILDIR_CUR);
	}
	if (tmpdir != NULL) {
		MALLOC(*tmpdir, len);
		snprintf(*tmpdir, len, "%s/%s", maildir, MAILDIR_TMP);
	}
	return 0;
}
