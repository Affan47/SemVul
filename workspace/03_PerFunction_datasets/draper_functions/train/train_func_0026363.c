setsymtab(char *n, char *s, Awkfloat f, unsigned t, Array *tp)
{
	int h;
	Cell *p;

	if (n != NULL && (p = lookup(n, tp)) != NULL) {
		   dprintf( ("setsymtab found %p: n=%s s=\"%s\" f=%g t=%o\n",
			p, p->nval, p->sval, p->fval, p->tval) );
		return(p);
	}
	p = (Cell *) malloc(sizeof(Cell));
	if (p == NULL)
		FATAL("out of space for symbol table at %s", n);
	p->nval = tostring(n);
	p->sval = s ? tostring(s) : tostring("");
	p->fval = f;
	p->tval = t;
	p->csub = CUNK;
	p->ctype = OCELL;
	tp->nelem++;
	if (tp->nelem > FULLTAB * tp->size)
		rehash(tp);
	h = hash(n, tp->size);
	p->cnext = tp->tab[h];
	tp->tab[h] = p;
	   dprintf( ("setsymtab set %p: n=%s s=\"%s\" f=%g t=%o\n",
		p, p->nval, p->sval, p->fval, p->tval) );
	return(p);
}
