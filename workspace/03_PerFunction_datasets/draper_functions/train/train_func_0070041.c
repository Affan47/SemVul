setshlineno(n)
long n;
{
	char tmp[strsize(ENVLINENO) + 1 + MAXLONGWIDTH + 1];

	if (shlineno < 0L) return;

	shlineno = n;
	VOID_C Xsnprintf(tmp, sizeof(tmp), "%s=%ld", ENVLINENO, n);
	shellvar = putvar(shellvar, Xstrdup(tmp), strsize(ENVLINENO));
}
