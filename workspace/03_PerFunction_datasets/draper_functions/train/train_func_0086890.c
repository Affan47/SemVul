Xreadlink(path, buf, bufsiz)
CONST char *path;
char *buf;
int bufsiz;
{
#ifdef	DEP_URLPATH
	char *host, tmp[MAXPATHLEN];
	int type;
#endif
#ifdef	FD
	char conv[MAXPATHLEN];
	int c;
#endif
	char lbuf[MAXPATHLEN];
	int n;

	path = convput(conv, path, 1, 0, lbuf, &c);
#ifdef	DEP_ROCKRIDGE
	if (*lbuf && (n = rrreadlink(lbuf, lbuf, sizeof(lbuf) - 1)) >= 0)
		;
	else
#endif
#ifdef	DEP_DOSEMU
	if (_dospath(path)) n = dosreadlink(path, lbuf, sizeof(lbuf) - 1);
	else
#endif
#ifdef	DEP_URLPATH
	if ((n = urlpath(path, &host, tmp, &type))) {
		n = urlreadlink(host, type, &(tmp[n]), lbuf, sizeof(lbuf) - 1);
		Xfree(host);
	}
	else
#endif
#if	MSDOS
	n = seterrno(EINVAL);
#else
	n = readlink(path, lbuf, sizeof(lbuf) - 1);
#endif

	if (n >= 0) {
		lbuf[n] = '\0';
#ifdef	DEP_KANJIPATH
		path = kanjiconv2(conv, lbuf,
			strsize(conv), c, DEFCODE, L_FNAME);
#else
		path = lbuf;
#endif
		for (n = 0; n < bufsiz && path[n]; n++) buf[n] = path[n];
	}

	return(n);
}
