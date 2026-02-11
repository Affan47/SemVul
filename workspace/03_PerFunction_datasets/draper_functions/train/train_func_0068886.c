parse_include(char *line, FILE * out)
{
	char *s = line, *fname;

	strsep(&s, "\"");
	if (s)
		fname = strsep(&s, "\"");
	if (!s) {
		IBWARN("bad include file name");
		return -1;
	}
	if (read_netconf(fname, out) < 0)
		return -1;
	return 1;
}
