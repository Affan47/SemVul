pmatch(const char *p, const char *s, unsigned len)
{
	for (;;) {
		char c = *p++;
		if (!c) return !len;
		switch (c) {
		case '*':
			c = *p;
			if (!c) return 1;
			for (;;) {
				if (!len) return 0;
				if (*s == c) break;
				++s;
				--len;
			}
			continue;
		case '+':
			c = *p++;
			if (c != *s) return 0;
			for (;;) {
				if (!len) return 1;
				if (*s != c) break;
				++s;
				--len;
			}
			continue;


		default:
			if (!len) return 0;
			if (*s != c) return 0;
			++s;
			--len;
			continue;
		}
	}
	return 0;
}
