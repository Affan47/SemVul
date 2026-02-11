GMT_compact_line (double *x, double *y, GMT_LONG n, GMT_LONG pen_flag, int *pen)
{

	GMT_LONG i, j;
	double old_slope, new_slope, dx;
	char *flag = NULL;

	if (n < 3) return (n);
	flag = (char *) GMT_memory (VNULL, (size_t)n, sizeof (char), "GMT_compact_line");

	dx = x[1] - x[0];
	old_slope = (GMT_IS_ZERO (dx)) ? copysign (HALF_DBL_MAX, y[1] - y[0]) : (y[1] - y[0]) / dx;

	for (i = 1; i < n-1; i++) {
		dx = x[i+1] - x[i];
		new_slope = (GMT_IS_ZERO (dx)) ? copysign (HALF_DBL_MAX, y[i+1] - y[i]) : (y[i+1] - y[i]) / dx;
		if (GMT_IS_ZERO (new_slope - old_slope) && !(pen_flag && (pen[i]+pen[i+1]) > 4))
			flag[i] = 1;
		else
			old_slope = new_slope;
	}

	for (i = j = 1; i < n; i++) {
		if (flag[i] == 0) {
			x[j] = x[i];
			y[j] = y[i];
			if (pen_flag) pen[j] = pen[i];
			j++;
		}
	}
	GMT_free ((void *)flag);

	return (j);
}
