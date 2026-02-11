table_delete(DB_DATABASE *db, char *table)
{
	int exit;
	SQLCHAR query[101] = "DROP TABLE ";

	strcpy((char *)&query[11], table);
	exit = do_query(db, "Cannot delete table:&1", NULL, (char *) query, 0);
	if (exit == 0)
	{
		exit = do_query(db, "Cannot delete table:&1", NULL, "COMMIT", 0);
	}

	return (exit);
}
