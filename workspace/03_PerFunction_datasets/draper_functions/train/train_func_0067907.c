ht_strnicmp(const char *s1, const char *s2, size_t max)
{
	if (!s1) return s2 ? -1 : 0;
	if (!s2) return s1 ? 1 : 0;
	while (max--) {
		if (!*s1) return *s2 ? -1 : 0;
		if (!*s2) return *s1 ? 1 : 0;
		char c1=tolower(*s1), c2=tolower(*s2);
		if (c1>c2) {
			return 1;
		} else if (c1<c2) {
			return -1;
		}
		s1++;s2++;
	}
	return 0;
}
