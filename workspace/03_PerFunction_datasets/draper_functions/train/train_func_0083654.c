ht_strcicomm(const char *s1, const char *s2)
{
	if (!s1 || !s2) return 0;
	int r=0;
	while (*s1 && *s2 && tolower(*s1) == tolower(*s2)) { s1++; s2++; r++; }
	return r;
}
