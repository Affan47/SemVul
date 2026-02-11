gsql_plugins_count()
{
	GSQL_TRACE_FUNC;

	g_return_val_if_fail (hash_plugins != NULL, 0);

	return g_hash_table_size (hash_plugins);
}
