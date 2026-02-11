tar_atol_base_n(const char *p, size_t char_cnt, int base)
{
	int64_t	l, limit, last_digit_limit;
	int digit, sign;

	limit = INT64_MAX / base;
	last_digit_limit = INT64_MAX % base;


	while (char_cnt != 0 && (*p == ' ' || *p == '\t')) {
		p++;
		char_cnt--;
	}

	sign = 1;
	if (char_cnt != 0 && *p == '-') {
		sign = -1;
		p++;
		char_cnt--;
	}

	l = 0;
	if (char_cnt != 0) {
		digit = *p - '0';
		while (digit >= 0 && digit < base  && char_cnt != 0) {
			if (l>limit || (l == limit && digit > last_digit_limit)) {
				l = INT64_MAX;
				break;
			}
			l = (l * base) + digit;
			digit = *++p - '0';
			char_cnt--;
		}
	}
	return (sign < 0) ? -l : l;
}
