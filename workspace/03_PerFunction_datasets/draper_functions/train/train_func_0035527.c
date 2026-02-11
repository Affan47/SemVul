bn_to_mon(u8 *d, u8 *N, u32 n)
{
	u32 i;

	for (i = 0; i < 8*n; i++)
		bn_add(d, d, d, N, n);
}
