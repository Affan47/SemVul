find_word()
{
    static char	SEPS[] = "#;&|^$=`'{}()<>\n\t ";
    ECHAR	*p;
    ECHAR	*new;
    ESIZE_T	len;

    for (p = &Line[Point]; p > Line && strchr(SEPS, (char)p[-1]) == NULL; p--)
	continue;
    len = Point - (p - Line) + 1;
    if ((new = NEW(ECHAR, len)) == NULL)
	return NULL;
    COPYFROMTO(new, p, len);
    new[len - 1] = '\0';
    return new;
}
