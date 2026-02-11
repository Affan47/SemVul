pcp_gmtime_s(const char *p)
{
	int y, m, d, hh, mm, ss;

	if (sscanf(p, "%4d%2d%2d%2d%2d%2d", &y, &m, &d, &hh, &mm, &ss)
	    != 6)
		return (0);
	return (pcp_gmtime(y, m, d, hh, mm, ss));
}
