gda_sql_statement_delete_copy (gpointer src)
{
	GdaSqlStatementDelete *dest;
	GdaSqlStatementDelete *delete = (GdaSqlStatementDelete *) src;

	dest = gda_sql_statement_delete_new ();

	dest->table = gda_sql_table_copy (delete->table);
	gda_sql_any_part_set_parent (dest->table, dest);

	dest->cond = gda_sql_expr_copy (delete->cond);
	gda_sql_any_part_set_parent (dest->cond, dest);

	return dest;
}
