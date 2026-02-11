xfitfunc(void *edata, double *x) {
	ubfit *uf = (ubfit *)edata;
	prand *s = uf->s;
	int i, e, di = s->di;
	double rv = 0.0;


	for (i = 0; i < uf->nvxs; i++) {
		double v[MXTD], ev;


		icxCubeInterp(x, di, di, v, uf->vxs[i].p);


		for (ev = 0.0, e = 0; e < di; e++) {
			double tt;
			tt = uf->vxs[i].v[e] - v[e];
			ev += tt * tt;
		}
		rv += ev;
	}
	return rv;
}
