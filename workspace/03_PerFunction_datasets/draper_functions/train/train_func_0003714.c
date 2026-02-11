get_pgstat_tabentry_relid(Oid relid, bool isshared, PgStat_StatDBEntry *shared,
						  PgStat_StatDBEntry *dbentry)
{
	PgStat_StatTabEntry *tabentry = NULL;

	if (isshared)
	{
		if (PointerIsValid(shared))
			tabentry = hash_search(shared->tables, &relid,
								   HASH_FIND, NULL);
	}
	else if (PointerIsValid(dbentry))
		tabentry = hash_search(dbentry->tables, &relid,
							   HASH_FIND, NULL);

	return tabentry;
}
