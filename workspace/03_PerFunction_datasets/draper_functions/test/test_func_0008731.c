bandval(mpp *p, int band, double *dev) {
	double tcnv[MPP_MXINKS];
	double tcnv1[MPP_MXINKS];
	double ww[MPP_MXINKS];
	int m, k;
	double ov;
	int j = band;


	for (m = 0; m < p->n; m++) {
		tcnv[m] = icxTransFunc(p->tc[m][j], p->cord, dev[m]);
		tcnv1[m] = 1.0 - tcnv[m];
	}

	if (p->useshape) {

		for (m = 0; m < p->n; m++)
			ww[m] = 0.0;


		for (k = 0; k < p->nn; k++) {
			double vv;
	 		for (vv = 1.0, m = 0; m < p->n; m++) {
				if (k & (1 << m))
					vv *= tcnv[m];
				else
					vv *= tcnv1[m];
			}
			for (m = 0; m < p->n; m++) {
				ww[m] += p->shape[m][k & ~(1<<m)][j] * vv;

			}
		}


		for (m = 0; m < p->n; m++) {
			double gg = ww[m];
			double vv = tcnv[m];
			if (gg >= 0.0) {
				vv = vv/(gg - gg * vv + 1.0);
			} else {
				vv = (vv - gg * vv)/(1.0 - gg * vv);
			}
			tcnv[m] = vv;
			tcnv1[m] = 1.0 - vv;
		}
	}


	for (ov = 0.0, k = 0; k < p->nn; k++) {
		double vv = p->pc[k][j];
		for (m = 0; m < p->n; m++) {
			if (k & (1 << m))
				vv *= tcnv[m];
			else
				vv *= tcnv1[m];
		}
		ov += vv;
	}

	return ov;
}
