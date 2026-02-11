rhythmdb_query_results_query_complete (RhythmDBQueryResults *results)
{
	RhythmDBQueryResultsIface *iface = RHYTHMDB_QUERY_RESULTS_GET_IFACE (results);
	if (iface->query_complete)
		iface->query_complete (results);
}
