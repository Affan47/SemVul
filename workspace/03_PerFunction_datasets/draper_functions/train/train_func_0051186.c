gnm_range_skew_pop (gnm_float const *xs, int n, gnm_float *res)
{
	gnm_float m, s, dxn, x3 = 0;
	int i;

	if (n < 1 || gnm_range_average (xs, n, &m) || gnm_range_stddev_pop (xs, n, &s))
		return 1;
	if (s == 0)
		return 1;

	for (i = 0; i < n; i++) {
		dxn = (xs[i] - m) / s;
		x3 += dxn * dxn *dxn;
	}

	*res = x3 / n;
	return 0;
}
