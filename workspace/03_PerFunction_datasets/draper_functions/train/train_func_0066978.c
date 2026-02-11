pg_johab_verifier(const unsigned char *s, int len)
{
	int			l,
				mbl;
	unsigned char c;

	l = mbl = pg_johab_mblen(s);

	if (len < l)
		return -1;

	if (!IS_HIGHBIT_SET(*s))
		return mbl;

	while (--l > 0)
	{
		c = *++s;
		if (!IS_EUC_RANGE_VALID(c))
			return -1;
	}
	return mbl;
}
