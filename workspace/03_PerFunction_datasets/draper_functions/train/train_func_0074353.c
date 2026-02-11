init_C_FP(void)
{
	int src, dst;
	int chunk, mask, value;

	memset(DES_C_FP, 0, sizeof(DES_C_FP));

	for (src = 0; src < 64; src++) {
		dst = DES_IP[ARCH_INDEX(DES_C[src])] ^ 7;

		chunk = src >> 2;
		mask = 1 << (src & 3);

		for (value = 0; value < 16; value++)
		if (value & mask)
#if ARCH_BITS >= 64
			DES_C_FP[chunk][value] |=
				(unsigned ARCH_WORD)1 << dst;
#else
			DES_C_FP[chunk][value][dst >> 5] |=
				(unsigned ARCH_WORD)1 << (dst & 0x1F);
#endif
	}
}
