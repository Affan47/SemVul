Info_RemoveKey (char *s, const char *key)
{
	char	*start;
	char	pkey[MAX_INFO_STRING];
	char	value[MAX_INFO_STRING];
	char	*o;

	if (strchr (key, '\\'))
	{
		Com_Printf ("Info_RemoveKey: Tried to remove illegal key '%s'\n", key);
		return;
	}

	while (1)
	{
		start = s;
		if (*s == '\\')
			s++;
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;

		s++;

		o = value;
		while (*s != '\\' && *s)
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;

		if (!strcmp (key, pkey) )
		{

			size_t memlen;

			memlen = strlen(s);
			memmove (start, s, memlen);
			*(start+memlen) = 0;
			return;
		}

		if (!*s)
			return;
	}
}
