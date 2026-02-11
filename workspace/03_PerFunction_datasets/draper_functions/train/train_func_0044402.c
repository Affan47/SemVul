factorial (int n)
{
	static const int cache[] = {
		1, 1, 2, 6, 24, 120,
		720, 5040, 40320, 362880, 3628800,
		39916800, 479001600
	};
	static const int CACHE_MAX = 12;
	int i, tot;

	if (n < 2)
		return 1;
	if (n <= CACHE_MAX)
		return cache[n];


	for (i = 13, tot = cache[12]; i <= n; ++i)
		tot *= i;

	return tot;
}
