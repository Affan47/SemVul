lookup(c)
char c;
{
    int ix = MAXMACROS;

    while (--ix >= 0 && mbuffer[ix].token != c)
	;
    return ix;
}
