indirect(Node **a, int n)
{
	Cell *x;
	int m;
	char *s;

	x = execute(a[0]);
	m = (int) getfval(x);
	if (m == 0 && !is_number(s = getsval(x)))
		FATAL("illegal field $(%s), name \"%s\"", s, x->nval);

	tempfree(x);
	x = fieldadr(m);
	x->ctype = OCELL;
	x->csub = CFLD;
	return(x);
}
