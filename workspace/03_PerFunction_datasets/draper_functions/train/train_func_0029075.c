at_user(const char *cp)
{
    size_t n = strcspn(cp, "-" ALPHA NUMERIC);
    if (n < 1)
	return 0;
    cp += n;

    if (*cp == ':')
    {
	n = strspn(cp + 1, ALPHA NUMERIC "-,?;.:/!%$^*&~\"#'");
	if (n > 0)
	    cp += 1 + n;
    }
    return cp;
}
