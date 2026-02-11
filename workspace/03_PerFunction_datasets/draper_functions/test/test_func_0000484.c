stirling (int n, int k)
{
	if (n == k)
		return 1;
	if ((n <= 0) || (k <= 0))
		return 0;
	if (k == 1)
		return Math::factorial (n - 1);
	if (n == (k + 1))
		return Math::choose (n, 2);
	if (k > n)
		return 0;

	return ((n - 1) * Math::stirling (n - 1, k) +
			Math::stirling (n - 1, k - 1));
}
