strl2llrc(const char *s, int len, long long *ret)
{
	long long i = 0;
	int j;

	if (!len)
		return 1;

	if (*s != '-') {

		while (len-- > 0) {
			j = (*s++) - '0';
			if (j > 9)              return 1;
			if (i > LLONG_MAX / 10LL) return 1;
			i = i * 10LL;
			if (i + j < i)          return 1;
			i = i + j;
		}
	} else {

		s++;
		while (--len > 0) {
			j = (*s++) - '0';
			if (j > 9)              return 1;
			if (i < LLONG_MIN / 10LL) return 1;
			i = i * 10LL;
			if (i - j > i)          return 1;
			i = i - j;
		}
	}
	*ret = i;
	return 0;
}
