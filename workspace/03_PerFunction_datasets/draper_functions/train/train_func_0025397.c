_midgard_sql_query_select_data_selector_get_query_result (MidgardQuerySelector *selector, GError **error)
{
	g_return_val_if_fail (selector != NULL, NULL);
	MidgardQueryExecutor *executor = MIDGARD_QUERY_EXECUTOR (selector);
	MidgardSqlQueryResult *query_result = midgard_sql_query_result_new (selector, G_OBJECT (executor->priv->resultset));

	guint n_objects;
	MidgardSqlQueryColumn **columns = midgard_sql_query_select_data_get_columns ((MidgardSqlQuerySelectData *)selector, &n_objects, NULL);
	if (columns != NULL)
		midgard_sql_query_result_set_columns (query_result, columns, n_objects, NULL);

	return  (MidgardQueryResult *) query_result;
}
