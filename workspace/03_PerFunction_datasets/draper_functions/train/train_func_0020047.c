GenerateBlock(byte *output, size_t size)
{
	while (size--)
	{
		word32 hi = seed/q;
		word32 lo = seed%q;

		long test = a*lo - r*hi;

		if (test > 0)
			seed = test;
		else
			seed = test+ m;

		*output++ = (GETBYTE(seed, 0) ^ GETBYTE(seed, 1) ^ GETBYTE(seed, 2) ^ GETBYTE(seed, 3));
	}
}
