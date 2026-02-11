readid(char *p, int fd)
{
	int l=IDBUFSIZE-1;

	while (l)
	{
		int n=read(fd, p, l);

		if (n < 0)
			return (-1);

		if (n == 0)
			break;

		p += n;
		l -= n;
	}
	*p=0;
	return 0;
}
