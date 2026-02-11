UT_strncasecmp (const char *s1, const char *s2, size_t n)
{
	int ret;

	if (n == 0)
		return 0;

	while ((ret = ((unsigned char) tolower (*s1) - (unsigned char) tolower (*s2))) == 0 && *s1++)
	{
		if (--n == 0)
			return 0;
		++s2;
	}
	return ret;
}
