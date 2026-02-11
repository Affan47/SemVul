getident()
{
    register int c;
    register char *idptr;
    register int length;
    register char *reglineptr;

    idptr = gsname;
    length = NAMESIZE;
    reglineptr = lineptr;
    c = ch;
more:
    do
    {
	*idptr++ = c;
	c = (unsigned char) *++reglineptr;
    }
    while (symofchar[c] <= MAXIDSYM && --length != 0);
    ch = c;
    *idptr = 0;
    debug(7, "Got ident %s", gsname);
    lineptr = reglineptr;
    if (symofchar[c] == SPECIALCHAR)
    {
	specialchar();
	if (SYMOFCHAR(ch) <= MAXIDSYM && length != 0)
	{
	    reglineptr = lineptr;
	    c = ch;
	    goto more;
	}
    }
}
