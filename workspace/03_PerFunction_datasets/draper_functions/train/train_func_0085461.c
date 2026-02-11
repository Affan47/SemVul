parsechar()
{
int	c;

	c=curchar();
	if (c == 0)	throw -1;
	nextchar();
	if (c != '\\') return (c);
	c=curchar();

	if (c == 0)
		throw -1;
	else if (c >= '0' && c <= '7')
	{
	unsigned char uc=0;

		while ( c >= '0' && c <= '7' )
		{
			uc = uc * 8 + (c-'0');
			nextchar();
			c=curchar();
		}
		c=uc;
	}
	else
	{
		c=backslash_char(c);
		nextchar();
	}
	return (c);
}
