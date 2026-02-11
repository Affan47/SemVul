builtinerror(argv, s, n)
char *CONST argv[];
CONST char *s;
int n;
{
	int duperrno;

	duperrno = errno;
	if (n >= BUILTINERRSIZ || (n < 0 && !errno)) return;
	if (argv && argv[0]) VOID_C Xfprintf(Xstderr, "%k: ", argv[0]);
	if (s) VOID_C Xfprintf(Xstderr, "%k: ", s);
	VOID_C Xfprintf(Xstderr,
		"%s.\n",
		(n >= 0 && builtinerrstr[n])
			? builtinerrstr[n] : Xstrerror(duperrno));
}
