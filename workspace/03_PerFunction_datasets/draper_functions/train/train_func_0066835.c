new_mcv_p(double *pp, int np) {
	int i;
	mcv *p;

	if ((p = new_mcv()) == NULL)
		return p;

	p->luord = np;
	if ((p->pms = (double *)calloc(p->luord, sizeof(double))) == NULL)
		error ("Malloc failed");

	for (i = 0; i < np; i++)
		p->pms[i] = *pp++;

	return p;
}
