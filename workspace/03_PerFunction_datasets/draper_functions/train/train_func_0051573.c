xcal_inv_interp(xcal *p, double *out, double *in) {
	int nsoln;
	co pp[MAX_INVSOLN];
	int j, k;
	double dir = 0.5;
	int rv = 0;

	for (j = 0; j < p->devchan; j++) {
		pp[0].v[0] = in[j];

		nsoln = p->cals[j]->rev_interp (
			p->cals[j],
			RSPL_NEARCLIP,
			MAX_INVSOLN,
			NULL,
			NULL,
			pp);

		nsoln &= RSPL_NOSOLNS;

		if (nsoln == 1) {
			k = 0;
		} else if (nsoln == 0) {
			rv = 1;
			return -1.0;
		} else {
			double bdist = 1e300;
			int bsoln = 0;
			for (k = 0; k < nsoln; k++) {
				double tt;
				tt = pp[k].p[0] - dir;
				tt *= tt;
				if (tt < bdist) {
					bdist = tt;
					bsoln = k;
				}
			}
			k = bsoln;
		}
		out[j] = pp[k].p[0];
	}

	return rv;
}
