table_FLIPUD (struct GMTMATH_INFO *info, double **stack[], GMT_LONG *constant, double *factor, GMT_LONG last, GMT_LONG col, GMT_LONG n_row)

{
	GMT_LONG i, k;

	if (constant[last]) return;
	if (gmtdefs.verbose && GMT_io.multi_segments[GMT_IN]) {
		fprintf (stderr, "%s: Warning, FLIPUD on multisegment file not supported!\n", GMT_program);
		return;
	}
	for (i = 0, k = n_row-1; i < n_row/2; i++, k--) d_swap (stack[last][col][i], stack[last][col][k]);
}
