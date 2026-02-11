regexp_escape_string(char *src, int anchor)
{
    char	*result, *dest;

    dest = result = XtMalloc(2 * strlen(src) + 3);

    if (anchor)
	*dest++ = '^';
    while (*src != '\0') {
	if (strchr("^.[$()|*+?{\\", *src))
	    *dest++ = '\\';
	*dest++ = *src++;
    }
    if (anchor)
	*dest++ = '$';
    *dest = '\0';

    return XtRealloc(result, strlen(result) + 1);
}
