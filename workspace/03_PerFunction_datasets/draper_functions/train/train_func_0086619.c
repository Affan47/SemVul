dnsq_solver(
	void *fdata,
	int n,
	double *x,
	double *fvec,
	int iflag
) {
	vopt_cx *cx = (vopt_cx *)fdata;
	ofps *s = cx->s;
	int k, e, di = s->di;
	int nn_1 = cx->nn-1;
	double sv[MXPD];
	double cee[MXPD+1], teperr;

#ifdef DUMP_FERR

	if (cx->debug) {
		if (cx->nl >= cx->_nl) {
			cx->_nl = 2 * cx->_nl + 5;
			if ((cx->clist = (loc *)realloc(cx->clist, sizeof(loc) * cx->_nl)) == NULL)
				error("ofps: malloc failed on debug location array %d", cx->_nl);
		}
		for (e = 0; e < di; e++)
			cx->clist[cx->nl].p[e] = x[e];
		cx->nl++;
	}
#endif


	ofps_cc_percept(s, sv, x);
	for (k = 0; k < cx->nn; k++)
		cee[k] = ofps_comp_eperr2(s, NULL, sv, x, cx->nds[k]->v, cx->nds[k]->p);


	for (teperr = 0.0, k = 0; k < cx->nn; k++)
		teperr += cee[k];
	teperr /= (double)cx->nn;

	for (k = e = 0; k < cx->nn; k++) {
		if (k != cx->on) {
			fvec[e++] = (teperr - cee[k]);
		}
	}


	for (k = 0; k < cx->nsp; k++) {
		pleq *pl = cx->sp[k];
		double v;

		for (v = pl->pe[di], e = 0; e < di; e++)
			v += pl->pe[e] * x[e];
		fvec[nn_1 + k] = FGPMUL * v;
	}

	s->funccount++;


	return 0;
}
