matchop(Node **a, int n)
{
	Cell *x, *y;
	char *s, *t;
	int i;
	void *p;

	x = execute(a[1]);
	s = getsval(x);
	if (a[0] == 0)
		p = (void *) a[2];
	else {
		y = execute(a[2]);
		t = getsval(y);
		p = compre(t);
		tempfree(y);
	}
	if (n == MATCHFCN)
		i = pmatch(p, s, s);
	else
		i = match(p, s, s);
	tempfree(x);
	if (n == MATCHFCN) {
		int start = countposn(s, patbeg-s)+1;
		if (patlen < 0)
			start = 0;
		setfval(rstartloc, (Awkfloat) start);
		setfval(rlengthloc, (Awkfloat) countposn(patbeg, patlen));
		x = gettemp();
		x->tval = NUM;
		x->fval = start;
		return x;
	} else if ((n == MATCH && i == 1) || (n == NOTMATCH && i == 0))
		return(True);
	else
		return(False);
}
