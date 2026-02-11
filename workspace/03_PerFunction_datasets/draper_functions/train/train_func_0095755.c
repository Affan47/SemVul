midgard_core_query_where_guid(
		const gchar *table, const gchar *guid)
{
	g_assert(guid != NULL);

	GString *where = g_string_new("");
	g_string_append_printf(where, "%s.guid = '%s' ", table, guid);

	return g_string_free(where, FALSE);
}
