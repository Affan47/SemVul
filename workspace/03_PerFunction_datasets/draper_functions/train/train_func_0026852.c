varname(char **s)
{
	Bufblock *b;
	char *cp;
	Rune r;
	int n;

	b = newbuf();
	cp = *s;
	for(;;){
		n = chartorune(&r, cp);
		if (!WORDCHR(r))
			break;
		rinsert(b, r);
		cp += n;
	}
	if (b->current == b->start){
		SYNERR(-1);
		fprint(2, "missing variable name <%s>\n", *s);
		freebuf(b);
		return 0;
	}
	*s = cp;
	insert(b, 0);
	return b;
}
