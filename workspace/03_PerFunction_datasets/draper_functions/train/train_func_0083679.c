db__recv_table_definition(dbTable ** table)
{
    int i, ncols;
    dbTable *t;

    DB_RECV_INT(&ncols);

    *table = t = db_alloc_table(ncols);
    if (t == NULL)
	return db_get_error_code();

    for (i = 0; i < t->numColumns; i++) {
	DB_RECV_COLUMN_DEFINITION(&t->columns[i]);
    }
    DB_RECV_STRING(&t->tableName);
    DB_RECV_STRING(&t->description);

    DB_RECV_INT(&t->priv_insert);
    DB_RECV_INT(&t->priv_delete);

    return DB_OK;
}
