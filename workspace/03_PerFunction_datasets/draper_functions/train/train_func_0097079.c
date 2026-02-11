streq_except_trailing_slash(const char *s1, const char *s2)
{
	int equal;

	if (!s1 && !s2)
		return 1;
	if (!s1 || !s2)
		return 0;

	equal = !strcmp(s1, s2);

	if (!equal) {
		size_t len1 = strlen(s1);
		size_t len2 = strlen(s2);

		if (len1 && *(s1 + len1 - 1) == '/')
			len1--;
		if (len2 && *(s2 + len2 - 1) == '/')
			len2--;
		if (len1 != len2)
			return 0;

		equal = !strncmp(s1, s2, len1);
	}

	return equal;
}
