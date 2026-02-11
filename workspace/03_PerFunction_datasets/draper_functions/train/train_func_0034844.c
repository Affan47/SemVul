gnm_range_multinomial (gnm_float const *xs, int n, gnm_float *res)
{
	gnm_float result = 1;
	int sum = 0;
	int i;

	for (i = 0; i < n; i++) {
		gnm_float x = xs[i];
		int xi;

		if (x < 0 || x > INT_MAX)
			return 1;

		xi = (int)x;
		if (sum == 0 || xi == 0)
			;
		else if (xi < 20) {
			int j;
			int f = sum + xi;

			result *= f--;
			for (j = 2; j <= xi; j++)
				result = result * f-- / j;
		} else {

			result *= combin (sum + xi, xi);
		}

		sum += xi;
	}

	*res = result;
	return 0;
}
