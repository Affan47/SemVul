gda_sql_statement_insert_take_extra_values_list (GdaSqlStatement *stmt, GSList *list)
{
	GSList *l1, *l2;
	GdaSqlStatementInsert *insert = (GdaSqlStatementInsert *) stmt->contents;
	for (l1 = list; l1; l1 = l1->next) {
		for (l2 = (GSList *) l1->data; l2; l2 = l2->next)
			gda_sql_any_part_set_parent (l2->data, insert);
	}
	insert->values_list = g_slist_concat (insert->values_list, list);
}
