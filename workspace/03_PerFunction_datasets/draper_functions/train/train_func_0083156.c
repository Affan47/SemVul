cob_cmp_long_numdisp (const unsigned char *data, const size_t size, const int n)
{
	const unsigned char	*p;
	long long		val = 0;
	size_t			inc;

	p = data;
	for (inc = 0; inc < size; inc++, p++) {
		val = (val * 10) + (*p - (unsigned char)'0');
	}
	return (val < n) ? -1 : (val > n);
}
