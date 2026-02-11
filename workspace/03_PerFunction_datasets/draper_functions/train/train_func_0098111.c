g2_qht_search_number_word(const tchar_t *s, size_t start, size_t len)
{
	uint32_t h;
	int b;

	for(h = 0, b = 0, s += start; len; len--, s++)
	{
		int v = *s;


		v   = (v < 'A' || v > 'Z' ? v : v + ('a' - 'A')) & 0xFF;
		v <<= b * BITS_PER_CHAR;


		b   = (b + 1) % 4;
		h  ^= v;
	}


	return g2_qht_hnumber(h, QHT_DEFAULT_BITS);
}
