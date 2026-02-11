utf8_decode_char_fast(const char *s, uint *retlen)
{
	uint32 uc = (uchar) *s;
	uint n = utf8_skip(uc);


	*retlen = n;

	if G_UNLIKELY(0 == n)
		return 0;
	else if (1 == n)
		return uc;
	else
		return utf8_decode_large_char_fast(s + 1, uc, retlen);
}
