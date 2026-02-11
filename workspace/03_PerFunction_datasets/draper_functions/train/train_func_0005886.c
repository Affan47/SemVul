build_row(char *p, unsigned *dp)
{
	unsigned col, val, day;

	memset(p, ' ', (julian + DAY_LEN) * 7);

	col = 0;
	do {
		day = *dp++;
		if (day != SPACE) {
			if (julian) {
				++p;
				if (day >= 100) {
					*p = '0';
					p[-1] = (day / 100) + '0';
					day %= 100;
				}
			}
			val = day / 10;
			if (val > 0) {
				*p = val + '0';
			}
			*++p = day % 10 + '0';
			p += 2;
		} else {
			p += DAY_LEN + julian;
		}
	} while (++col < 7);

	return p;
}
