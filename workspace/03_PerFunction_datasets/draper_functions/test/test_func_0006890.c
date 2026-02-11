comp_pcs(
xifs *p,
double auxw,
double *auxrv,
double *auxv,
double *pcs,
double *dev
) {
	int i;
	double rv;
	double ss[MAX_CHAN];
	double check[3];
#ifdef NEVER
double start[3];
double auxst[1];
double auxch[1];
p->clutipcsfunc(p->cbctx, start, NULL, auxst, dev);
#endif

	p->m_auxw = auxw;

	for (i = 0; i < p->daux; i++)
		p->m_auxv[i] = auxv[i];

	for (i = 0; i < 3; i++)
		p->m_pcs[i] = pcs[i];


	for (i = 0; i < p->dout; i++)
		ss[i] = 0.3;

	if (powell(&rv, p->dout, dev, ss, 0.001, 1000, minfunc, p, NULL, NULL) != 0) {
		return 1;
	}


	for (i = 0; i < p->dout; i++) {
		double v = dev[i];
		if (v < 0.0)
			v = 0.0;
		else if (v > 1.0)
			v = 1.0;
		dev[i] = v;
	}

	if (auxrv != NULL) {
		p->clutipcsfunc(p->cbctx, check, NULL, auxrv, dev);
	}

#ifdef NEVER
p->clutipcsfunc(p->cbctx, check, NULL, auxch, dev);
printf("~9 comp_pcs target    aux %f  PCS %f %f %f\n", auxv[0], pcs[0], pcs[1], pcs[2]);
printf("~9          returning error %f on %f %f %f %f\n", rv, dev[0], dev[1], dev[2], dev[3]);
printf("~9          PCS start  = %f %f %f (%f)\n",start[0], start[1], start[2],
                                                  absdiffn(3, start, pcs));
printf("~9          PCS finish = %f %f %f (%f)\n",check[0], check[1], check[2],
                                                  absdiffn(3, check, pcs));
printf("~9          PCS delta = %f, aux delta = %f\n", absdiffn(3, start, check),
                                                       fabs(auxst[0] - auxch[0]));
#endif

	return 0;
}
