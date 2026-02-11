git__prefixcmp(const char *str, const char *prefix)
{
	for (;;) {
		char p = *(prefix++), s;
		if (!p)
			return 0;
		if ((s = *(str++)) != p)
			return s - p;
	}
}
