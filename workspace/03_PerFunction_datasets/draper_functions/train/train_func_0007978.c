GetTokenIndex(char *token, char **list, int len, char **next)
{
	int i;
	int l;
	int k;

	if (!token || !list)
	{
		if (next)
		{
			*next = NULL;
		}
		return -1;
	}
	l = (len) ? len : strlen(token);
	for (i = 0; list[i] != NULL; i++)
	{
		k = strlen(list[i]);
		if (len < 0)
		{
			l = k;
		}
		else if (len == 0 && k != l)
		{
			continue;
		}
		if (!strncasecmp(token, list[i], l))
		{
			break;
		}
	}
	if (next)
	{
		*next = (list[i]) ? token + l : token;
	}

	return (list[i]) ? i : -1;
}
