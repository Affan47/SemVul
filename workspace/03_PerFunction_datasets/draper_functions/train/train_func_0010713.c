check_request(void *_object, char *contentType, char *data, int len)
{
	int i;
	unsigned char c;

	if (THIS_STATUS > 0)
	{
		GB.Error(ERR_STILL_ACTIVE);
		return TRUE;
	}

	if (!contentType)
	{
		GB.Error(ERR_INVALID_CONTENT_TYPE);
		return TRUE;
	}

	for (i = 0; i < strlen(contentType); i++)
	{
		c = contentType[i];
		if (isalnum(c) || c == '-' || c == '+' || c == '.' || c == '/' || c == ';' || c == ' ' || c == '=')
			continue;
		GB.Error(ERR_INVALID_CONTENT_TYPE);
		return TRUE;
	}

	if (!data || !len)
	{
		GB.Error(ERR_INVALID_DATA);
		return TRUE;
	};

	return FALSE;
}
