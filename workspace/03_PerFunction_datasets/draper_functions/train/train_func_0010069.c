pgstat_get_tab_entry(PgStat_StatDBEntry *dbentry, Oid tableoid, bool create)
{
	PgStat_StatTabEntry *result;
	bool		found;
	HASHACTION	action = (create ? HASH_ENTER : HASH_FIND);


	result = (PgStat_StatTabEntry *) hash_search(dbentry->tables,
												 &tableoid,
												 action, &found);

	if (!create && !found)
		return NULL;


	if (!found)
	{
		result->numscans = 0;
		result->tuples_returned = 0;
		result->tuples_fetched = 0;
		result->tuples_inserted = 0;
		result->tuples_updated = 0;
		result->tuples_deleted = 0;
		result->tuples_hot_updated = 0;
		result->n_live_tuples = 0;
		result->n_dead_tuples = 0;
		result->changes_since_analyze = 0;
		result->blocks_fetched = 0;
		result->blocks_hit = 0;
		result->vacuum_timestamp = 0;
		result->vacuum_count = 0;
		result->autovac_vacuum_timestamp = 0;
		result->autovac_vacuum_count = 0;
		result->analyze_timestamp = 0;
		result->analyze_count = 0;
		result->autovac_analyze_timestamp = 0;
		result->autovac_analyze_count = 0;
	}

	return result;
}
