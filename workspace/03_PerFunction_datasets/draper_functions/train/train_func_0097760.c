init_bm_table(unsigned char *needle, size_t table[UCHAR_MAX + 1], size_t len, int casesensitive,
				   int searchtype)
{
	size_t	i = 0, j = 0, currentindex = 0;

	for (i = 0; i <= UCHAR_MAX; i++)
		table[i] = len;
	for (i = 0; i < len; i++)
		{
		if (searchtype == SEARCHTYPE_REVERSE)
			{

			currentindex = i;

			}
		else
			{
			currentindex = len - i - 1;
			}

		if (needle[i] == wildcard)
			{
			for (j = 0; j <= UCHAR_MAX; j++)
				table[j] = currentindex;
			}

		table[(unsigned char)needle[i]] = currentindex;
		if (!casesensitive)
			{


			table[tolower(needle[i])] = currentindex;
			table[toupper(needle[i])] = currentindex;
			}
		}
}
