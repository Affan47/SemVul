utf8_decode_large_char_fast(const char *s, uint32 uc, uint *retlen)
{
	uchar c = *s;
	uint i = uc & 0x3F;
	uint n = *retlen;


	if (c > utf8_2nd_byte_tab[i].end || c < utf8_2nd_byte_tab[i].start)
		goto failure;

	n--;
	uc &= 0x3F >> n;

	for (;;) {
		uc = UTF8_ACCUMULATE(uc, c);
		if (--n == 0)
			break;
		c = *++s;


		if (0x80 != (0xC0 & c))
			goto failure;
	}


	if (0xFFFE == (0xFFFE & uc))
		goto failure;

	return uc;

failure:
	*retlen = 0;
	return 0;
}
