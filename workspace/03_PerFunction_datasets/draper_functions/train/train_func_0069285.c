format_number(int64_t v, char *p, int s, int maxsize, int strict)
{
	int64_t limit;

	limit = ((int64_t)1 << (s*3));


	if (strict)
		return (format_octal(v, p, s));


	if (v >= 0) {
		while (s <= maxsize) {
			if (v < limit)
				return (format_octal(v, p, s));
			s++;
			limit <<= 3;
		}
	}


	return (format_256(v, p, maxsize));
}
