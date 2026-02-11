DB_SubstString(const char *pattern, int len_pattern, DB_SUBST_CALLBACK add)
{
	int i;
	unsigned char last_c, c;
	int n;
	char quote[20] = {0};

	c = 0;

	len_pattern--;
	for (i = 0; i < len_pattern; i++)
	{
		last_c = c;
		c = pattern[i];

		if (c == '&')
		{
			c = pattern[++i];
			if (c == '&')
				continue;
			if (isdigit(c))
			{
				n = c - '0';
				c = pattern[++i];
				if (isdigit(c))
				{
					n = n * 10 + c - '0';
					i++;
				}
				quote[n] = last_c;
			}
		}
	}

	_quote_cb = add;
	_quote = quote;

	return GB.SubstString(pattern, len_pattern, ss_get_param);
}
