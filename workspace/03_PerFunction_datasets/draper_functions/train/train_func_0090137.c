bn_mon_mul(u8 *d, u8 *a, u8 *b, u8 *N, u32 n)
{
	u8 t[512];
	u32 i;

	bn_zero(t, n);

	for (i = n - 1; i < n; i--)
		bn_mon_muladd_dig(t, a, b[i], N, n);

	bn_copy(d, t, n);
}
