ofps_comp_eperr(
	ofps *s,
	double *pddist,
	double *v,
	double *p,
	double *nv,
	double *np
) {
	int ii, e, f, di = s->di;
	int isc;
	double tt, ddist, pdist;
	double eperr;


#ifndef NEVER

#if MXPD > 4
# error "ofps.c: Need to expand switch  code for MXPD > 4"
#endif

	pdist = ddist = 0.0;
	switch (di) {
		case 4:
			tt = (p[3] - np[3]);
			ddist += tt * tt;
			tt = (v[3] - nv[3]);
			pdist += tt * tt;
		case 3:
			tt = (p[2] - np[2]);
			ddist += tt * tt;
			tt = (v[2] - nv[2]);
			pdist += tt * tt;
		case 2:
			tt = (p[1] - np[1]);
			ddist += tt * tt;
			tt = (v[1] - nv[1]);
			pdist += tt * tt;
		case 1:
			tt = (p[0] - np[0]);
			ddist += tt * tt;
			tt = (v[0] - nv[0]);
			pdist += tt * tt;
	}
#else

	for (pdist = ddist = 0.0, e = 0; e < di; e++) {


		tt = (p[e] - np[e]);
		ddist += tt * tt;


		tt = (v[e] - nv[e]);
		pdist += tt * tt;
	}
#endif

	if (pddist != NULL)
		*pddist = ddist;

	ddist *= 100.0 * 100.0;


	ddist = sqrt(ddist);
	pdist = sqrt(pdist);
	eperr = s->devd_wght * ddist + s->perc_wght * pdist;


	return eperr;
}
