freevar(var)
char **var;
{
	int i, duperrno;

	duperrno = errno;
	if (var) {
		for (i = 0; var[i]; i++) Xfree(var[i]);
		Xfree(var);
	}
	errno = duperrno;
}
