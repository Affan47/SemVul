grd_AND (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	GMT_LONG prev, i;
	double a, b;

	prev = last - 1;
	for (i = 0; i < info->nm; i++) {
		a = (constant[prev]) ? factor[prev] : stack[prev][i];
		b = (constant[last]) ? factor[last] : stack[last][i];
		stack[prev][i] = (float)((GMT_is_dnan (a)) ? b : a);
	}
}
