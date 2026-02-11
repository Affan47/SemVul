midgard_core_qb_add_table(MidgardQueryBuilder *builder, const gchar *table)
{
	g_assert(builder != NULL);
	g_assert(table != NULL);

	g_hash_table_insert(builder->priv->tables, g_strdup((gchar *) table), NULL);

	return ;
}
