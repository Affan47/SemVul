dir_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (
#ifndef WIN32
			*s1 != *s2
#else

			pg_tolower((unsigned char) *s1) != pg_tolower((unsigned char) *s2)
#endif
			&& !(IS_DIR_SEP(*s1) && IS_DIR_SEP(*s2)))
			return (int) *s1 - (int) *s2;
		s1++, s2++;
	}
	if (*s1)
		return 1;
	if (*s2)
		return -1;
	return 0;
}
