truncate_identifier(char *ident, int len, bool warn)
{
	if (len >= NAMEDATALEN)
	{
		len = pg_mbcliplen(ident, len, NAMEDATALEN - 1);
		if (warn)
		{


			char	buf[NAMEDATALEN];

			memcpy(buf, ident, len);
			buf[len] = '\0';
			ereport(NOTICE,
					(errcode(ERRCODE_NAME_TOO_LONG),
					 errmsg("identifier \"%s\" will be truncated to \"%s\"",
							ident, buf)));
		}
		ident[len] = '\0';
	}
}
