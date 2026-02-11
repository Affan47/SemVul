check_crlf(const char *value)
{
	if (GIT_ATTR_TRUE(value))
		return GIT_CRLF_TEXT;

	if (GIT_ATTR_FALSE(value))
		return GIT_CRLF_BINARY;

	if (GIT_ATTR_UNSPECIFIED(value))
		return GIT_CRLF_GUESS;

	if (strcmp(value, "input") == 0)
		return GIT_CRLF_INPUT;

	if (strcmp(value, "auto") == 0)
		return GIT_CRLF_AUTO;

	return GIT_CRLF_GUESS;
}
