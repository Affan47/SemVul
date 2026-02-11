rfc822hdr_namecmp(const char *a, const char *b)
{
	int rc;

	while ((rc=(int)(unsigned char)lc(*a) - (int)(unsigned char)lc(*b))==0)
	{
		if (!*a)
			return 0;
		++a;
		++b;
	}

	return rc;
}
