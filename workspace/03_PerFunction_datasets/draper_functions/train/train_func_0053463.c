grd_PLMg (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	GMT_LONG prev, first, L, M, i;
	double a = 0.0;

	prev  = last - 1;
	first = prev - 1;

	if (!(constant[prev] && constant[last])) {
		fprintf (stderr, "%s: L and M must be constants in PLMg!\n", GMT_program);
		exit (EXIT_FAILURE);
	}

	L = irint (factor[prev]);
	M = irint (factor[last]);

	if (constant[first]) a = GMT_plm_bar (L, M, factor[first], FALSE);
	for (i = 0; i < info->nm; i++) stack[first][i] = (float)((constant[first]) ? a : GMT_plm_bar (L, M, stack[first][i], FALSE));
}
