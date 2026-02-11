div64by32lo(int64 *src, unsigned int d)
{
	unsigned int lo, hi, q, s, mask;

	lo = src->lo; hi = src->hi;

#if ARCH_INT_GT_32
	hi += lo >> 32;
	lo &= 0xFFFFFFFF;
#endif

	if (hi >= d) return 0xFFFFFFFF;

	q = 0; mask = 0x80000000;
	do {
		s = hi;
		hi = (hi << 1) | (lo >> 31);
		lo <<= 1;

#if ARCH_INT_GT_32
		lo &= 0xFFFFFFFF;
#endif

		if ((s & 0x80000000) || hi >= d) {
			hi -= d;
			q |= mask;
		}
	} while (mask >>= 1);

	return q;
}
