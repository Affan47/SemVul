allocset(struct parse *p)
{
	int no = p->g->ncsets++;
	size_t nc;
	size_t nbytes;
	cset *cs;
	size_t css = (size_t)p->g->csetsize;
	int i;

	if (no >= p->ncsalloc) {
		void *ptr;

		p->ncsalloc += CHAR_BIT;
		nc = p->ncsalloc;
		if (nc > SIZE_MAX / sizeof(cset))
			goto nomem;
		assert(nc % CHAR_BIT == 0);
		nbytes = nc / CHAR_BIT * css;

		ptr = (cset *)realloc((char *)p->g->sets, nc * sizeof(cset));
		if (ptr == NULL)
			goto nomem;
		p->g->sets = ptr;

		ptr = (uch *)realloc((char *)p->g->setbits, nbytes);
		if (ptr == NULL)
			goto nomem;
		p->g->setbits = ptr;

		for (i = 0; i < no; i++)
			p->g->sets[i].ptr = p->g->setbits + css*(i/CHAR_BIT);

		(void) memset((char *)p->g->setbits + (nbytes - css), 0, css);
	}

	if (p->g->sets == NULL || p->g->setbits == NULL)
		goto nomem;

	cs = &p->g->sets[no];
	cs->ptr = p->g->setbits + css*((no)/CHAR_BIT);
	cs->mask = 1 << ((no) % CHAR_BIT);
	cs->hash = 0;
	cs->smultis = 0;
	cs->multis = NULL;

	return(cs);
nomem:
	free(p->g->sets);
	p->g->sets = NULL;
	free(p->g->setbits);
	p->g->setbits = NULL;

	SETERROR(REG_ESPACE);

	return(NULL);
}
