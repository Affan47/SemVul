pattern(cp, cnt)
register char *cp;
register int cnt;
{
    register char c;
    c = 0;
    while( cnt-- > 0 )  {
	while( !isprint((c&0x7F)) )  c++;
	*cp++ = (c++&0x7F);
    }
}
