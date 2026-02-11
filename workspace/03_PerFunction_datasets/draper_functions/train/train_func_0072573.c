freemacro(n)
int n;
{
	int i;

	if (!ismacro(n)) return(-1);

	Xfree(macrolist[n - FUNCLISTSIZ]);
	memmove((char *)&(macrolist[n - FUNCLISTSIZ]),
		(char *)&(macrolist[n - FUNCLISTSIZ + 1]),
		(--maxmacro - (n - FUNCLISTSIZ)) * sizeof(*macrolist));

	for (i = 0; i < maxbind; i++) {
		if (ismacro(ffunc(i)) && ffunc(i) > n) ffunc(i)--;
		if (ismacro(dfunc(i)) && dfunc(i) > n) dfunc(i)--;
	}

	return(0);
}
