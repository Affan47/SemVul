pg_utf8_verifier(const unsigned char *s, int len)
{
	int			l = pg_utf_mblen(s);

	if (len < l)
		return -1;

	if (!pg_utf8_islegal(s, l))
		return -1;

	return l;
}
