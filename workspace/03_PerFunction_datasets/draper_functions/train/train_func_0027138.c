open_temp(HTAB *hashp)
{
#ifdef XP_OS2
 	hashp->fp = mkstemp(NULL);
#else
#if !defined(_WIN32) && !defined(_WINDOWS) && !defined(macintosh)
	sigset_t set, oset;
#endif
#if !defined(macintosh)
	char * tmpdir;
	size_t len;
	char last;
#endif
	static const char namestr[] = "/_hashXXXXXX";
	char filename[1024];

#if !defined(_WIN32) && !defined(_WINDOWS) && !defined(macintosh)

	(void)sigfillset(&set);
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
#endif

	filename[0] = 0;
#if defined(macintosh)
	strcat(filename, namestr + 1);
#else
	tmpdir = getenv("TMP");
	if (!tmpdir)
		tmpdir = getenv("TMPDIR");
	if (!tmpdir)
		tmpdir = getenv("TEMP");
	if (!tmpdir)
		tmpdir = ".";
	len = strlen(tmpdir);
	if (len && len < (sizeof filename - sizeof namestr)) {
		strcpy(filename, tmpdir);
	}
	len = strlen(filename);
	last = tmpdir[len - 1];
	strcat(filename, (last == '/' || last == '\\') ? namestr + 1 : namestr);
#endif

#if defined(_WIN32) || defined(_WINDOWS)
	if ((hashp->fp = mkstempflags(filename, _O_BINARY|_O_TEMPORARY)) != -1) {
		if (hashp->filename) {
			free(hashp->filename);
		}
		hashp->filename = strdup(filename);
		hashp->is_temp = 1;
	}
#else
	if ((hashp->fp = mkstemp(filename)) != -1) {
		(void)unlink(filename);
#if !defined(macintosh)
		(void)fcntl(hashp->fp, F_SETFD, 1);
#endif
	}
#endif

#if !defined(_WIN32) && !defined(_WINDOWS) && !defined(macintosh)
	(void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
#endif
#endif
	return (hashp->fp != -1 ? 0 : -1);
}
