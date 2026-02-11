_get_suffixed_integer_arguments(
	char *action, char **ret_action, int *retvals, int num,
	char *suffixlist, int *ret_suffixnum, char *parsestring)
{
	int i;
	int j;
	int n;
	char *token;
	int suffixes;


	suffixes = 0;
	if (suffixlist != 0)
	{

		suffixes = strlen(suffixlist);
	}

	for (i = 0; i < num && action; i++)
	{
		token = PeekToken(action, &action);
		if (token == NULL)
		{
			break;
		}
		if (sscanf(token, parsestring, &(retvals[i]), &n) < 1)
		{
			break;
		}
		if (suffixes != 0 && ret_suffixnum != NULL)
		{
			int len;
			char c;

			len = strlen(token) - 1;
			c = token[len];
			if (isupper(c))
			{
				c = tolower(c);
			}
			for (j = 0; j < suffixes; j++)
			{
				char c2 = suffixlist[j];

				if (isupper(c2))
				{
					c2 = tolower(c2);
				}
				if (c == c2)
				{
					ret_suffixnum[i] = j+1;
					break;
				}
			}
			if (j == suffixes)
			{
				ret_suffixnum[i] = 0;
			}
		}
		else if (token[n] != 0 && !isspace(token[n]))
		{

			break;
		}
	}
	if (ret_action != NULL)
	{
		*ret_action = action;
	}

	return i;
}
