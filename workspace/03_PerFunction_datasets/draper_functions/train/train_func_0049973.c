execruncom(fname, verbose)
CONST char *fname;
int verbose;
{
#ifdef	MINIMUMSHELL
	char *cp, path[MAXPATHLEN];
#endif
	lockbuf_t *lck;
	char *new, **dupargvar;
	int ret, duprestricted;

	setsignal();
#ifdef	MINIMUMSHELL
	if (*fname == '~' && fname[1] == _SC_ && (cp = getconstvar(ENVHOME))) {
		strcatdelim2(path, cp, &(fname[2]));
		fname = path;
	}
#endif
	new = Xstrdup(fname);
#if	MSDOS && !defined (BSPATHDELIM)
	new = adjustpname(new);
#endif
	fname = new = evalpath(new, 0);
	ret = RET_SUCCESS;
	if (noruncom || !isrootdir(fname)) lck = NULL;
	else if (!(lck = lockopen(fname, O_TEXT | O_RDONLY, 0666))) {
		doperror(NULL, fname);
		ret = RET_FAIL;
	}
	else if (lck -> fd >= 0) {
#ifdef	FD
		inruncom = 1;
#endif
		duprestricted = restricted;
		restricted = 0;
		dupargvar = argvar;
		argvar = (char **)Xmalloc(2 * sizeof(char *));
		argvar[0] = Xstrdup(fname);
		argvar[1] = NULL;
		ret = sourcefile(lck -> fd, fname, verbose);
		freevar(argvar);
		argvar = dupargvar;
		restricted = duprestricted;
#ifdef	FD
		inruncom = 0;
#endif
	}
	lockclose(lck);
	resetsignal(0);
	Xfree(new);

	return(ret);
}
