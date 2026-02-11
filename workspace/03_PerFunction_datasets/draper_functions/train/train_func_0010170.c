_scan_nan(u_int32_t *words, int num_words, const char *s)
{
	int si;
	int bitpos;

	memset(words, 0, num_words * sizeof(u_int32_t));


	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s += 2;


	for (si = 0; isxdigit(s[si]); si++)
		;


#if _BYTE_ORDER == _LITTLE_ENDIAN
	for (bitpos = 0; bitpos < 32 * num_words; bitpos += 4) {
#else
	for (bitpos = 32 * num_words - 4; bitpos >= 0; bitpos -= 4) {
#endif
		if (--si < 0)
			break;
		words[bitpos / 32] |= digittoint(s[si]) << (bitpos % 32);
	}
}
