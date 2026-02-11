slapi_u64_to_hex(uint64_t val, char *s, uint8_t upper) {
	static char ldigits[] = "0123456789abcdef";
	static char udigits[] = "0123456789ABCDEF";
	char *digits;

	if (upper) {
		digits = udigits;
	} else {
		digits = ldigits;
	}
	s[0] = digits[val >> 60];
	s[1] = digits[(val >> 56) & 0xf];
	s[2] = digits[(val >> 52) & 0xf];
	s[3] = digits[(val >> 48) & 0xf];
	s[4] = digits[(val >> 44) & 0xf];
	s[5] = digits[(val >> 40) & 0xf];
	s[6] = digits[(val >> 36) & 0xf];
	s[7] = digits[(val >> 32) & 0xf];
	s[8] = digits[(val >> 28) & 0xf];
	s[9] = digits[(val >> 24) & 0xf];
	s[10] = digits[(val >> 20) & 0xf];
	s[11] = digits[(val >> 16) & 0xf];
	s[12] = digits[(val >> 12) & 0xf];
	s[13] = digits[(val >> 8) & 0xf];
	s[14] = digits[(val >> 4) & 0xf];
	s[15] = digits[val & 0xf];
	return &s[16];
}
