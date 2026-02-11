search(const char *src, int len, const char *list, int start, bool not)
{
	int i;
	char c;

	for (i = start; i < len; i++)
	{
		c = src[i];

		if (c == '\\')
		{
			i++;
			if (i >= len)
				break;
			c = src[i];
		}

		if ((index(list, c) != NULL) ^ not)
			return i;
	}

	return len;
}
