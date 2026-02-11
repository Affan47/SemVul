awkdelete(Node **a, int n)
{
	Cell *x, *y;
	Node *np;
	char *s;
	int nsub = strlen(*SUBSEP);

	x = execute(a[0]);
	if (!isarr(x))
		return True;
	if (a[1] == 0) {
		freesymtab(x);
		x->tval &= ~STR;
		x->tval |= ARR;
		x->sval = (char *) makesymtab(NSYMTAB);
	} else {
		int bufsz = recsize;
		char *buf;
		if ((buf = (char *) malloc(bufsz)) == NULL)
			FATAL("out of memory in adelete");
		buf[0] = 0;
		for (np = a[1]; np; np = np->nnext) {
			y = execute(np);
			s = getsval(y);
			if (!adjbuf(&buf, &bufsz, strlen(buf)+strlen(s)+nsub+1, recsize, 0, 0))
				FATAL("out of memory deleting %s[%s...]", x->nval, buf);
			strcat(buf, s);
			if (np->nnext)
				strcat(buf, *SUBSEP);
			tempfree(y);
		}
		freeelem(x, buf);
		free(buf);
	}
	tempfree(x);
	return True;
}
