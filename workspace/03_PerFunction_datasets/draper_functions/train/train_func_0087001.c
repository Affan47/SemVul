Log2
	(
	uint32 n
	)
{
	int result = 0;
	for (n = n>>1; n; n = n>>1)
		result++;
	return result;
}
