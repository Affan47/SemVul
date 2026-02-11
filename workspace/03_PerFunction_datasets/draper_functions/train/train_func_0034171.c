crc32_pclmul_le(u32 crc, unsigned char const *p, size_t len)
{
	unsigned int iquotient;
	unsigned int iremainder;
	unsigned int prealign;

	if (len < PCLMUL_MIN_LEN + SCALE_F_MASK || !irq_fpu_usable())
		return crc32_le(crc, p, len);

	if ((long)p & SCALE_F_MASK) {

		prealign = SCALE_F - ((long)p & SCALE_F_MASK);

		crc = crc32_le(crc, p, prealign);
		len -= prealign;
		p = (unsigned char *)(((unsigned long)p + SCALE_F_MASK) &
				     ~SCALE_F_MASK);
	}
	iquotient = len & (~SCALE_F_MASK);
	iremainder = len & SCALE_F_MASK;

	kernel_fpu_begin();
	crc = crc32_pclmul_le_16(p, iquotient, crc);
	kernel_fpu_end();

	if (iremainder)
		crc = crc32_le(crc, p + iquotient, iremainder);

	return crc;
}
