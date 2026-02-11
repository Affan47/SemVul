gnm_range_avedev (gnm_float const *xs, int n, gnm_float *res)
{
	if (n > 0) {
		gnm_float m, s = 0;
		int i;

		gnm_range_average (xs, n, &m);
		for (i = 0; i < n; i++)
			s += gnm_abs (xs[i] - m);
		*res = s / n;
		return 0;
	} else
		return 1;
}
