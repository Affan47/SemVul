strextcmp(const char *s1, const char *s2)
{

	Assert( (s1 != NULL) && (s2 != NULL) );


	char *s1_end = (char *)strrchr(s1, '.');
	char *s2_end = (char *)strrchr(s2, '.');


	size_t s1_len, s2_len;

	if (s1_end != NULL)
		s1_len = (s1_end - s1);
	else
		s1_len = strlen(s1);

	if (s2_end != NULL)
		s2_len = (s2_end - s2);
	else
		s2_len = strlen(s2);


	if (s2_len != s1_len)
		return 1;

	return strnicmp(s1, s2, s1_len);
}
