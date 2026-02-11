savebuf(char *p, int l)
{
	while (l)
	{
	int	n=write(childpipe, p, l);

		if (n <= 0)	return (-1);
		p += n;
		l -= n;
	}
	return (0);
}
