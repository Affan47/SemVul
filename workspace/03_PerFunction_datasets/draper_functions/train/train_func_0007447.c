Com_ParseExt (char **data_p, qboolean allowNewLines)
{
	int c, len = 0;
	char *data;
	qboolean hasNewLines = false;

	data = *data_p;
	com_token[0] = 0;


	if (!data)
	{
		*data_p = NULL;
		return com_token;
	}


	while (1)
	{

		data = Com_SkipWhiteSpace(data, &hasNewLines);
		if (!data)
		{
			*data_p = NULL;
			return com_token;
		}

		if (hasNewLines && !allowNewLines)
		{
			*data_p = data;
			return com_token;
		}

		c = *data;


		if (c == '/' && data[1] == '/')
		{
			while (*data && *data != '\n')
			data++;
		}


		else if (c == '/' && data[1] == '*')
		{
			data += 2;

			while (*data && (*data != '*' || data[1] != '/'))
			{
				if (*data == '\n')
					com_parseLine++;

				data++;
			}

			if (*data)
			data += 2;
		}


			else
			break;
	}


	if (c == '\"')
	{
		data++;
		while (1)
		{
			c = *data++;
			if (c == '\n')
				com_parseLine++;

			if (c == '\"' || !c)
			{
				*data_p = data;
				com_token[len] = 0;
				return com_token;
			}
			if (len < MAX_TOKEN_CHARS)
			com_token[len++] = c;
		}
	}


	do
	{
		if (len < MAX_TOKEN_CHARS)
			com_token[len++] = c;

		data++;
		c = *data;
	} while (c > 32);

	if (len == MAX_TOKEN_CHARS)
		len = 0;

	com_token[len] = 0;

	*data_p = data;
	return com_token;
}
