kgetc(mp)
char_u	*	mp;
{
	int		c;

	if (helppos >= helpsize)
		c = EOF;
	else
	{
		c = helpmem[helppos];
		helppos++;
	}
	return(c);
}
