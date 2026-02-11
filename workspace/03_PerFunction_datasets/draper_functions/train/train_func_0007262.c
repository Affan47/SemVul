isform(const char *d1, const char *d2, const char *f)
{
	char	*d;
	int	sret;
	struct	stat	sbuf;

	if  (strchr(DEF_SUFCHARS, f[0]))
		return  0;

	d = pathjoin(d1, d2, f);
	sret = stat(d, &sbuf);
	free(d);
	return  sret >= 0  &&  (sbuf.st_mode & S_IFMT) == S_IFREG  &&  sbuf.st_uid == Daemuid;
}
