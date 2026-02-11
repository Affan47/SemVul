redupil(long double x)
{
	long double t;
	long i;

	t = x / PIL;
	if (t >= 0.0L)
		t += 0.5L;
	else
		t -= 0.5L;

	i = t;
	t = i;
	t = ((x - t * DP1) - t * DP2) - t * DP3;
	return (t);
}
