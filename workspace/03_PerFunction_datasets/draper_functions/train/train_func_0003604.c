doschmod(path, mode)
CONST char *path;
int mode;
{
	int n, dd;

	if ((dd = getdent(path, NULL)) < 0) return(seterrno(doserrno));
	dd2dentp(dd) -> attr = getdosmode((u_int)mode);
	if ((n = writedent(dd)) < 0) errno = doserrno;
	dosclosedev(dd);

	return(n);
}
