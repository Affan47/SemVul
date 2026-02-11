copyostr2str(char *sstr, long ssi, long num, STRING *dstr, long dsi)
{
	size_t len;
	char	*c, *c1;

	len = strlen(sstr);

	if (num < 0 || (size_t)(ssi + num) > len)
		num = len - ssi;
	if (num <= 0)
		return 0;
	if (dsi < 0)
		dsi = 0;
	if ((size_t)(dsi + num) > dstr->s_len)
		num = dstr->s_len - dsi;
	c1 = sstr + ssi;
	c = dstr->s_str + dsi;
	while (num-- > 0)
		*c++ = *c1++;
	return 0;
}
