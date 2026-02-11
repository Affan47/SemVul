unicode_utf8_fromu(const unicode_char *cp, int *ip)
{
	char *p=0;
	int pass;
	size_t l=0;

	for (pass=0; pass<2; pass++)
	{
		if (pass)
		{
			p=malloc(l+1);
			if (!p)
			{
				if (ip)	*ip= -1;
				return (0);
			}
		}

		l=unicode_utf8_fromu_pass(cp, p);
		if (pass)
			p[l]=0;
	}
	return (p);
}
