completeexe(file, len, argc, argvp)
CONST char *file;
int len, argc;
char ***argvp;
{
	char *cp, *tmp, *next;
	int dlen;

# ifdef	CWDINPATH
	argc = completefile(file, len, argc, argvp, curpath, 1, 2);
# endif
	if (!(next = getconstvar(ENVPATH))) return(argc);
	for (cp = next; cp; cp = next) {
# ifdef	DEP_DOSPATH
		if (_dospath(cp)) next = Xstrchr(&(cp[2]), PATHDELIM);
		else
# endif
		next = Xstrchr(cp, PATHDELIM);
		dlen = (next) ? (next++) - cp : strlen(cp);
		tmp = _evalpath(cp, &(cp[dlen]), 0);
		dlen = strlen(tmp);
		argc = completefile(file, len, argc, argvp, tmp, dlen, 2);
		Xfree(tmp);
	}

	return(argc);
}
