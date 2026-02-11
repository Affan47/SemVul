collection_table_sync_idle_cb(gpointer data)
{
	CollectTable *ct = data;

	if (!ct->sync_idle_id) return FALSE;
	g_source_remove(ct->sync_idle_id);
	ct->sync_idle_id = 0;

	collection_table_sync(ct);
	return FALSE;
}
