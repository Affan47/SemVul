get_dydx_range(double* ximg, double* yimg, int nimg,
                           double* xcat, double* ycat, int ncat,
                           double *mindx, double *mindy,
                           double *maxdx, double *maxdy) {
	int i, j;
	*maxdx = -1e100;
	*mindx = 1e100;
	*maxdy = -1e100;
	*mindy = 1e100;

	for (i = 0; i < nimg; i++) {
		for (j = 0; j < ncat; j++) {
			double dx = ximg[i] - xcat[j];
			double dy = yimg[i] - ycat[j];
			*maxdx = MAX(dx, *maxdx);
			*maxdy = MAX(dy, *maxdy);
			*mindx = MIN(dx, *mindx);
			*mindy = MIN(dy, *mindy);
		}
	}
}
