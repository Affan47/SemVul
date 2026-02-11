strcount(const char *haystack, const char *needle)
{
	size_t i = 0, nlen = strlen(needle);

	while ((haystack = strstr(haystack, needle)) != NULL) {
		i++;
		haystack += nlen;
	}
	return i;
}
