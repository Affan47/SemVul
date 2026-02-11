table_ACSC (struct GMTMATH_INFO *info, double **stack[], GMT_LONG *constant, double *factor, GMT_LONG last, GMT_LONG col, GMT_LONG n_row)

{
	GMT_LONG i;
	double a = 0.0;

	if (gmtdefs.verbose && constant[last] && fabs (factor[last]) > 1.0) fprintf (stderr, "%s: Warning, |operand| > 1 for ACSC!\n", GMT_program);
	if (constant[last]) a = d_asin (1.0 / factor[last]);
	for (i = 0; i < n_row; i++) stack[last][col][i] = (constant[last]) ? a : d_asin (1.0 / stack[last][col][i]);
}
