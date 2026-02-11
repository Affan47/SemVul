dequote_txt(const char *src, size_t len, char *dst)
{
	char ch;
	size_t i, j;
	FLAG quote;

	for (i = j = 0, quote = 0; i < len; i++) {
		ch = src[i];
		if (TCLR(quote) || !(quote = ch == '\\'))
			dst[j++] = ch;
	}
	dst[j] = '\0';

	return j;
}
