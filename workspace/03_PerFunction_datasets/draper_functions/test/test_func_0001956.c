SUBR_file(ushort code)
{
	int i;
	int length;
	char *addr;
	int len;
	char *str, *ptr;
	bool slash;

	SUBR_ENTER();

	length = 0;
	slash = FALSE;

	for (i = 0; i < NPARAM; i++)
	{

		SUBR_get_string_len(&PARAM[i], &addr, &len);

		if (len > 0)
		{
			if (length > 0)
			{
				if (!slash && addr[0] != '/')
					length++;
				else if (slash && addr[0] == '/')
					length--;
			}

			slash = addr[len - 1] == '/';

			length += len;
		}

	}

	str = STRING_new(NULL, length);
	ptr = str;
	slash = FALSE;

	i = NPARAM;
	while (i--)
	{
		VALUE_get_string(PARAM, &addr, &len);

		if (len > 0)
		{
			if (ptr > str)
			{
				if (!slash && *addr != '/')
					*ptr++ = '/';
				else if (slash && *addr == '/')
					ptr--;
			}

			slash = addr[len - 1] == '/';

			memcpy(ptr, addr, len);
			ptr += len;
		}

		RELEASE_STRING(PARAM);
		PARAM++;
	}

	SP -= NPARAM;
	SP->type = T_STRING;
	SP->_string.addr = str;
	SP->_string.start = 0;
	SP->_string.len = length;
	SP++;
}
