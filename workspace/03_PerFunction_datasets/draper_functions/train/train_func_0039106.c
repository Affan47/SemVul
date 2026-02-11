pg_char_to_encname_struct(const char *name)
{
	unsigned int nel = pg_encname_tbl_sz;
	pg_encname *base = pg_encname_tbl,
			   *last = base + nel - 1,
			   *position;
	int			result;
	char		buff[NAMEDATALEN],
			   *key;

	if (name == NULL || *name == '\0')
		return NULL;

	if (strlen(name) >= NAMEDATALEN)
	{
#ifdef FRONTEND
		fprintf(stderr, "encoding name too long\n");
		return NULL;
#else
		ereport(ERROR,
				(errcode(ERRCODE_NAME_TOO_LONG),
				 errmsg("encoding name too long")));
#endif
	}
	key = clean_encoding_name(name, buff);

	while (last >= base)
	{
		position = base + ((last - base) >> 1);
		result = key[0] - position->name[0];

		if (result == 0)
		{
			result = strcmp(key, position->name);
			if (result == 0)
				return position;
		}
		if (result < 0)
			last = position - 1;
		else
			base = position + 1;
	}
	return NULL;
}
