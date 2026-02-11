myinet_aton(const char *s)
{
    unsigned long a, b, c, d;
    int elements;
    char junk;

    if (!s)
	return 0;
    elements = sscanf(s, "%lu.%lu.%lu.%lu%c", &a, &b, &c, &d, &junk);
    if (!(elements == 4 || (elements == 5 && junk == '/')))
	return 0;
    if (a > 255 || b > 255 || c > 255 || d > 255)
	return 0;
    return (a << 24) + (b << 16) + (c << 8) + d;
}
