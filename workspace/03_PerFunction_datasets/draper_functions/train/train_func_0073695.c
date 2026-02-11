CheckDateTokenTable(const char *tablename, const datetkn *base, int nel)
{
	bool		ok = true;
	int			i;

	for (i = 0; i < nel; i++)
	{

		if (strlen(base[i].token) > TOKMAXLEN)
		{

			elog(LOG, "token too long in %s table: \"%.*s\"",
				 tablename,
				 TOKMAXLEN + 1, base[i].token);
			ok = false;
			break;
		}

		if (i > 0 &&
			strcmp(base[i - 1].token, base[i].token) >= 0)
		{
			elog(LOG, "ordering error in %s table: \"%s\" >= \"%s\"",
				 tablename,
				 base[i - 1].token,
				 base[i].token);
			ok = false;
		}
	}
	return ok;
}
