dequote(char *p)
{
	char *q;

	for (q=p; *q; q++)
	{
		if (*q == '+' && q[1] && q[2])
		{
			*p++=nybble(q[1])*16 + nybble(q[2]);
			q += 2;
			continue;
		}
		*p++=*q;
	}
	*p=0;
}
