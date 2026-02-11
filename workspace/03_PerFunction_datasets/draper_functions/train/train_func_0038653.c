make_human_readable_str(unsigned long long val,
	unsigned long block_size, unsigned long display_unit)
{
	static const char unit_chars[] ALIGN1 = {
		'\0', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'
	};

	static char *str;

	unsigned frac;
	const char *u;
	const char *fmt;

	if (val == 0)
		return "0";

	fmt = "%llu";
	if (block_size > 1)
		val *= block_size;
	frac = 0;
	u = unit_chars;

	if (display_unit) {
		val += display_unit/2;
		val /= display_unit;

	} else {
		while ((val >= 1024)

		) {
			fmt = "%llu.%u%c";
			u++;
			frac = (((unsigned)val % 1024) * 10 + 1024/2) / 1024;
			val /= 1024;
		}
		if (frac >= 10) {
			++val;
			frac = 0;
		}
#if 1

		if (block_size == 0) {
			if (frac >= 5) {
				++val;
			}
			fmt = "%llu%*c";
			frac = 1;
		}
#endif
	}

	if (!str) {

		str = xmalloc(sizeof(val)*3 + 2 + 3);
	}
	sprintf(str, fmt, val, frac, *u);
	return str;
}
