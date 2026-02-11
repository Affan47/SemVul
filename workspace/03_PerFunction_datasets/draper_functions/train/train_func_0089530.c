find_kword(cgats *p, int table, const char *ksym) {
	int i;
	cgats_table *t;

	p->errc = 0;
	p->err[0] = '\000';

	if (table < 0 || table >= p->ntables)
		return err(p, -2, "cgats.find_kword(), table number '%d' is out of range",table);
	t = &p->t[table];

	if (ksym == NULL || ksym[0] == '\000')
		return -1;

	for (i = 0; i < t->nkwords; i ++) {
		if (t->ksym[i] != NULL && t->kdata[i] != NULL
		    && strcmp(t->ksym[i],ksym) == 0)
			return i;
	}

	return -1;
}
