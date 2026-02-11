grd_RAND (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	GMT_LONG i, prev;
	double a = 0.0, b = 0.0;

	prev = last - 1;
	if (constant[prev]) a = factor[prev];
	if (constant[last]) b = factor[last];
	for (i = 0; i < info->nm; i++) {
		if (!constant[prev]) a = (double)stack[prev][i];
		if (!constant[last]) b = (double)stack[last][i];
		stack[prev][i] = (float)(a + GMT_rand () * (b - a));
	}
}
