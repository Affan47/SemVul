validacl(const char *p)
{
	while (*p)
	{
		if ((int)(unsigned char)*p <= ' ')
		{
			errno=EINVAL;
			return -1;
		}
		++p;
	}

	return 0;
}
