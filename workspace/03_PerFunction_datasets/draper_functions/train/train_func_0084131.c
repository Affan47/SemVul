range_lcm (gnm_float const *xs, int n, gnm_float *res)
{
	int i;
	gnm_float lcm;

	if (n <= 0)
		return 1;

	lcm = 1;
	for (i = 0; i < n; i++) {
		gnm_float thisx = gnm_fake_floor (xs[i]);
		if (thisx == 1)
			continue;
		if (thisx < 1 || thisx > gnm_gcd_max || lcm > gnm_gcd_max)
			return 1;
		lcm = gnm_lcm (lcm, thisx);
	}

	*res = lcm;
	return 0;
}
