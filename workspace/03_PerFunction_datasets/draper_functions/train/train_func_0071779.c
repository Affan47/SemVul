utils_strpos(const gchar *haystack, const gchar *needle)
{
	const gchar *sub;

	if (! *needle)
		return -1;

	sub = strstr(haystack, needle);
	if (! sub)
		return -1;

	return sub - haystack;
}
