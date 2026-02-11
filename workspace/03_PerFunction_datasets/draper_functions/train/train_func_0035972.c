grd_PSI (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	GMT_LONG i;
	double a = 0.0, x[2];

	x[1] = 0.0;
	if (constant[last]) {
		x[0] = factor[last];
		a = GMT_psi (x, (double *)NULL);
	}

	for (i = 0; i < info->nm; i++) {
		if (!constant[last]) {
			x[0] = (double)stack[last][i];
			a = GMT_psi (x, (double *)NULL);
		}
		stack[last][i] = (float)a;
	}
}
