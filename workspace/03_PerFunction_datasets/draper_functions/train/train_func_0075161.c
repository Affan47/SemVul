pgstat_fetch_stat_funcentry(Oid func_id)
{
	PgStat_StatDBEntry *dbentry;
	PgStat_StatFuncEntry *funcentry = NULL;


	backend_read_statsfile();


	dbentry = pgstat_fetch_stat_dbentry(MyDatabaseId);
	if (dbentry != NULL && dbentry->functions != NULL)
	{
		funcentry = (PgStat_StatFuncEntry *) hash_search(dbentry->functions,
														 (void *) &func_id,
														 HASH_FIND, NULL);
	}

	return funcentry;
}
