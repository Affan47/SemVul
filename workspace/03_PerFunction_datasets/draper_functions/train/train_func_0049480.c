addends_for(int target, int n, int max)
{
	int a_min;
	int a_max;

	if (target < 1 || n < 1)
		return 0;

	if (n == 1) {
		if (target >= 1 && target <= max)
			return CDOK_SET_SINGLE(target);

		return 0;
	}

	a_min = target - max * (n - 1);
	if (a_min < 1)
		a_min = 1;

	a_max = target - (n - 1);
	if (a_max > max)
		a_max = max;

	if (a_min > a_max)
		return 0;

	return CDOK_SET_RANGE(a_min, a_max);
}
