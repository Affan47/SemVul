pg_wchar2utf_with_len(const pg_wchar *from, unsigned char *to, int len)
{
	int			cnt = 0;

	while (len > 0 && *from)
	{
		int char_len;

		unicode_to_utf8(*from, to);
		char_len = pg_utf_mblen(to);
		cnt += char_len;
		to += char_len;
		from++;
		len--;
	}
	*to = 0;
	return cnt;
}
