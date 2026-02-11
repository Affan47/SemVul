print_db_infos(DbInfoArr *db_arr)
{
	int			dbnum;

	for (dbnum = 0; dbnum < db_arr->ndbs; dbnum++)
	{
		pg_log(PG_VERBOSE, "Database: %s\n", db_arr->dbs[dbnum].db_name);
		print_rel_infos(&db_arr->dbs[dbnum].rel_arr);
		pg_log(PG_VERBOSE, "\n\n");
	}
}
