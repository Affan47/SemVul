nextchar(char **s)
{
	char c, *pps;

	c = *(*s)++;
	pps = *s;
	if (c == '\\')
		c = bb_process_escape_sequence((const char**)s);
	if (c == '\\' && *s == pps) {
		c = *(*s);
		if (c)
			(*s)++;
	}
	return c;
}
