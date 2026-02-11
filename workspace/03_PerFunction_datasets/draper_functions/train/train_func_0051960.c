utf8dupucs2(const char *utf8str)
{
	size_t ucs2_size = 	utf8toucs2(NULL, 0, utf8str, strlen(utf8str)) + 1;
	ucs2_char_t* dst = (ucs2_char_t*)malloc(ucs2_size * sizeof(ucs2_char_t));
	if (dst) {
		utf8toucs2(dst, ucs2_size * sizeof(ucs2_char_t), utf8str, strlen(utf8str)+1);
	}
	return dst;
}
