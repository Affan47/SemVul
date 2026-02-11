chdir2(path)
CONST char *path;
{
	char cwd[MAXPATHLEN], tmp[MAXPATHLEN];
	int duperrno;

#ifdef	DEBUG
	if (!path) {
		Xfree(lastpath);
		lastpath = NULL;
# ifdef	DEP_PSEUDOPATH
		Xfree(unixpath);
		unixpath = NULL;
# endif
		return(0);
	}
#endif

	Xrealpath(path, tmp, (physical_path) ? RLP_READLINK : 0);
	Xstrcpy(cwd, fullpath);
	Xstrcpy(fullpath, tmp);

	if (_chdir2(fullpath) < 0) {
		duperrno = errno;
		if (_chdir2(cwd) < 0) lostcwd(fullpath);
		else Xstrcpy(fullpath, cwd);
		errno = duperrno;
		return(-1);
	}
	Xfree(lastpath);
	lastpath = Xstrdup(cwd);
#ifdef	DEP_PSEUDOPATH
	switch (checkdrv(lastdrv, NULL)) {
# ifdef	DEP_DOSDRIVE
		case DEV_DOS:
			if (!unixpath) unixpath = Xstrdup(cwd);
			if (Xgetwd(cwd)) Xstrcpy(fullpath, cwd);
			Xrealpath(fullpath, fullpath, 0);
			break;
# endif
# ifdef	DEP_URLPATH
		case DEV_URL:
			if (!unixpath) unixpath = Xstrdup(cwd);
			break;
# endif
		default:
			Xfree(unixpath);
			unixpath = NULL;
			break;
	}
#endif
	if (getconstvar(ENVPWD)) setenv2(ENVPWD, fullpath, 1);
#if	MSDOS
	if (unixrealpath(fullpath, tmp)) Xstrcpy(fullpath, tmp);
#endif
	VOID_C entryhist(fullpath, HST_PATH | HST_UNIQ);
#ifdef	DEP_PTY
	sendparent(TE_CHDIR, fullpath);
#endif

	return(0);
}
