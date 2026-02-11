db_alloc_cursor_table(dbCursor * cursor, int ncols)
{
    cursor->table = db_alloc_table(ncols);
    if (cursor->table == NULL)
	return db_get_error_code();
    return DB_OK;
}
