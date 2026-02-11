dump_string(char *output, int maxlen, void *value, int len)
{
	if (maxlen > len + 1)
		maxlen = len + 1;

	snprintf(output, maxlen, "%s", (char *) value);
}
