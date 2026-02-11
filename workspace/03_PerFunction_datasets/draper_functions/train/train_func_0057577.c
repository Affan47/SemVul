xdevlin_invlin(
struct _xdevlin *p,
double *out,
double *in
) {
	int i, j;
	int nsoln;
	co pp[MAX_INVSOLN];
	double cdir;

	for (i = 0; i < p->di; i++) {
		pp[0].p[0] = p->clipc[i];
		pp[0].v[0] = in[i];
		cdir = p->clipc[i] - in[i];

		nsoln = p->curves[i]->rev_interp (
			p->curves[i],
			0,
			MAX_INVSOLN,
			NULL,
			&cdir,
			pp);

		nsoln &= RSPL_NOSOLNS;

		if (nsoln == 1) {
			j = 0;
		} else if (nsoln == 0) {
			error("~~~1 Unexpected failure to find reverse solution for linearisation curve");
			return;
		} else {

			double bdist = 1e300;
			int bsoln = 0;

printf("~~~1 got %d reverse solutions\n",nsoln);
printf("~~~1 solution 0 = %f\n",pp[0].p[0]);
printf("~~~1 solution 1 = %f\n",pp[1].p[0]);
			for (j = 0; j < nsoln; j++) {
				double tt;
				tt = pp[i].p[0] - p->clipc[i];
				tt *= tt;
				if (tt < bdist) {
					bdist = tt;
					bsoln = j;
				}
			}
			j = bsoln;
		}
		out[i] = pp[j].p[0];
	}
}
