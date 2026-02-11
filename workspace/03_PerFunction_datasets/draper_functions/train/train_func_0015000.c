grd_UPPER (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	GMT_LONG i;
	float high;

	if (constant[last]) {
		for (i = 0; i < info->nm; i++) stack[last][i] = (float)factor[last];
		return;
	}

	for (i = 0, high = -FLT_MAX; i < info->nm; i++) {
		if (GMT_is_fnan (stack[last][i])) continue;
		if (stack[last][i] > high) high = stack[last][i];
	}
	for (i = 0; i < info->nm; i++) if (!GMT_is_fnan (stack[last][i])) stack[last][i] = high;
}
