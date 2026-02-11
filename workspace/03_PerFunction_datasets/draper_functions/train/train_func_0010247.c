text_nfind2(const char *text, const char *end, char c, size_t count)
{
	while (text < end)
	{
		if (*text == c)
		{
			if (count > 0)
			{
				count--;
			}
			else
			{
				return (char *) text;
			}
		}

		text++;
	}

	return (char *) text;
}
