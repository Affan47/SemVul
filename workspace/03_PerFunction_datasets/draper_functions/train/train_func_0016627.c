setexecpath(argv, envp)
CONST char *argv;
char *CONST envp[];
{
	CONST char *cp;
	char *tmp, buf[MAXPATHLEN];

	if (!Xgetwd(buf)) {
		errno = 0;
		error("No current working directory.");
	}
	origpath = Xstrdup(buf);
	if ((cp = searchenv(ENVPWD, envp))) {
		*fullpath = '\0';
		Xrealpath(cp, fullpath, 0);
		Xrealpath(fullpath, buf, RLP_READLINK);
		if (!strpathcmp(origpath, buf)) {
			Xfree(origpath);
			origpath = Xstrdup(fullpath);
		}
	}
	Xstrcpy(fullpath, origpath);

	tmp = NULL;
#if	MSDOS
	cp = argv;
#else
	if (strdelim(argv, 0)) cp = argv;
	else cp = tmp = searchexecname(argv, envp);
	if (!cp) progpath = Xstrdup(BINDIR);
	else
#endif
	{
		Xrealpath(cp, buf, RLP_READLINK);
		Xfree(tmp);
		if ((tmp = strrdelim(buf, 0))) *tmp = '\0';
		progpath = Xstrdup(buf);
	}
}
