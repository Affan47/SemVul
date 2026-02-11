copy_field(const char *start, const char *end)
{
    char	*ret, *c;
    long	n = end - start;

    ret = XtMalloc(n + 1);
    memcpy(ret, start, n);
    ret[n] = '\0';

    for (c = strchr(ret, '\n') ; c ; c = strchr(c, '\n'))
	*c++ = ' ';

    return ret;
}
