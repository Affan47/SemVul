rand_init(UINT8 *rng, int size, int left, int right, int add)
{
    int mask = (1 << size) - 1;
    int i, x = 0;

	LOG_RAND(("rand %d\n", size));
    for( i = 0; i < mask; i++ )
	{
		if (size == 17)
			*rng = x >> 6;
		else
			*rng = x;
        LOG_RAND(("%05x: %02x\n", x, *rng));
        rng++;

		x = ((x << left) + (x >> right) + add) & mask;
	}
}
