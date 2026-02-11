namematch(const char *end, const char *start, const char *match)
{
	int len = strlen(match);
	return ((end-len >= start) && (strncmp(end-len, match, len) == 0));
}
