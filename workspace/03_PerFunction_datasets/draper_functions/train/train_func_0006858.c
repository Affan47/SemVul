mkdirpath(char *filename, void (*report)(const char *, ...)) {
	char *slash = strrchr(filename, '/');
	char strbuf[ISC_STRERRORSIZE];
	unsigned int mode;

	if (slash != NULL && slash != filename) {
		struct stat sb;
		*slash = '\0';

		if (stat(filename, &sb) == -1) {
			if (errno != ENOENT) {
				isc__strerror(errno, strbuf, sizeof(strbuf));
				(*report)("couldn't stat '%s': %s", filename,
					  strbuf);
				goto error;
			}
			if (mkdirpath(filename, report) == -1)
				goto error;


			if (!strcmp(slash + 1, "") ||
			    !strcmp(slash + 1, ".") ||
			    !strcmp(slash + 1, "..")) {
				*slash = '/';
				return (0);
			}
			mode = S_IRUSR | S_IWUSR | S_IXUSR;
			mode |= S_IRGRP | S_IXGRP;
			mode |= S_IROTH | S_IXOTH;
			if (mkdir(filename, mode) == -1) {
				isc__strerror(errno, strbuf, sizeof(strbuf));
				(*report)("couldn't mkdir '%s': %s", filename,
					  strbuf);
				goto error;
			}
			if (runas_pw != NULL &&
			    chown(filename, runas_pw->pw_uid,
				  runas_pw->pw_gid) == -1) {
				isc__strerror(errno, strbuf, sizeof(strbuf));
				(*report)("couldn't chown '%s': %s", filename,
					  strbuf);
			}
		}
		*slash = '/';
	}
	return (0);

 error:
	*slash = '/';
	return (-1);
}
