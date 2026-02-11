field_exist(DB_DATABASE *db, const char *table, const char *field)
{
	const char *query =
			"show columns from `&1` like '&2'";

	MYSQL_RES *res;
	int exist;

	if (do_query(db, "Unable to check field: &1", &res, query, 2, table, field))
		return FALSE;

	exist = !search_result(res, field, NULL);
	mysql_free_result(res);

	return exist;
}
