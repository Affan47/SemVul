ast_odbc_clear_cache(const char *database, const char *tablename)
{
	struct odbc_cache_tables *tableptr;

	AST_RWLIST_WRLOCK(&odbc_tables);
	AST_RWLIST_TRAVERSE_SAFE_BEGIN(&odbc_tables, tableptr, list) {
		if (strcmp(tableptr->connection, database) == 0 && strcmp(tableptr->table, tablename) == 0) {
			AST_LIST_REMOVE_CURRENT(list);
			destroy_table_cache(tableptr);
			break;
		}
	}
	AST_RWLIST_TRAVERSE_SAFE_END
	AST_RWLIST_UNLOCK(&odbc_tables);
	return tableptr ? 0 : -1;
}
