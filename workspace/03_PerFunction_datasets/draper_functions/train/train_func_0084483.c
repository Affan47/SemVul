at_news(const char *cp)
{
    if (memcmp(cp, "news:", 5) != 0)
	return 0;
    cp += 5;
    size_t n = strspn(cp, "-" ALPHA NUMERIC "\\^_{|}~!\"#$%&'()*+,./;:=?`");
    if (n < 1)
	return 0;
    cp += n;
    if (*cp++ != '@')
	return 0;
    cp = at_host_dot(cp);
    if (!cp)
	return 0;
    if (*cp == ':')
    {
	const char *end = at_number(cp + 1);
	if (end)
	    cp = end;
    }
    return cp;
}
