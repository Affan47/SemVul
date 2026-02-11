poly_init(UINT8 *poly, int size, int left, int right, int add)
{
	int mask = (1 << size) - 1;
    int i, x = 0;

	LOG_POLY(("poly %d\n", size));
	for( i = 0; i < mask; i++ )
	{
		*poly++ = x & 1;
		LOG_POLY(("%05x: %d\n", x, x&1));

		x = ((x << left) + (x >> right) + add) & mask;
	}
}
