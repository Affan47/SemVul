char2uni(const unsigned char *rawstring, int boundlen,
			wchar_t *uni)
{
	unsigned char ch, cl;
	const wchar_t *charset2uni;
	int n;

	if (boundlen <= 0)
		return -ENAMETOOLONG;

	if (boundlen == 1) {
		if (rawstring[0]==0x80) {
			*uni = 0x20ac;
		} else {
			*uni = rawstring[0];
		}
		return 1;
	}

	ch = rawstring[0];
	cl = rawstring[1];

	charset2uni = page_charset2uni[ch];
	if (charset2uni && cl) {
		*uni = charset2uni[cl];
		if (*uni == 0x0000)
			return -EINVAL;
		n = 2;
	} else{
		if (ch==0x80) {
			*uni = 0x20ac;
		} else {
			*uni = ch;
		}
		n = 1;
	}
	return n;
}
