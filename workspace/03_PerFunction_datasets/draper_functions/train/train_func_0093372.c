index_list(DB_DATABASE *db, const char *table, char ***indexes)
{
	const char *query = "show index from `&1`";

	MYSQL_RES *res;
	MYSQL_ROW row;
	long i, n, no_indexes;

	if (do_query(db, "Unable to get indexes: &1", &res, query, 1, table))
		return -1;

	for ( i = 0, no_indexes = 0; i < mysql_num_rows(res); i++ )
	{


		row = mysql_fetch_row(res);
		if ( atoi(row[3]) == 1)
				no_indexes++;
	}


	GB.NewArray(indexes, sizeof(char *), no_indexes);
	mysql_data_seek(res, 0);

	for ( i = 0, n = 0; i < mysql_num_rows(res); i++ )
	{
		row = mysql_fetch_row(res);
		if ( atoi(row[3]) == 1 )
			(*indexes)[n++] = GB.NewZeroString(row[2]);
	}

	mysql_free_result(res);
	return no_indexes;
}
