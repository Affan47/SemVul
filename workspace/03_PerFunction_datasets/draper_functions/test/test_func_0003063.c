is_strsuffix(const char *str, size_t len, const char *suffix)
{
	size_t suffix_len;

	g_assert(NULL != str);
	g_assert(NULL != suffix);

	len = (size_t)-1 == len ? strlen(str) : len;
	suffix_len = strlen(suffix);

	if (suffix_len > len) {
		return FALSE;
	} else {
		const char *p = &str[len - suffix_len];
		return 0 == memcmp(p, suffix, suffix_len);
	}
}
