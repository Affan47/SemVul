squote(char *cp, int c)
{
	Rune r;
	int n;

	while(*cp){
		n = chartorune(&r, cp);
		if(r == c)
			return cp;
		if(r == '\\')
			n += chartorune(&r, cp+n);
		cp += n;
	}
	SYNERR(-1);
	fprint(2, "missing closing '\n");
	return 0;
}
