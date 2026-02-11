pixbuf_cache_entry_toggle_ref(const gchar * key, GdkPixbuf * pb, gboolean is_last_ref)
{
	g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Toggle Reference called: %i:%s", is_last_ref, key);
	if (is_last_ref)
	{
		DCE *e = g_hash_table_lookup(pb_cache, key);
		if (e)
			e->in_use = FALSE;
		if (timeout > 0)
			g_source_remove(timeout);
		g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "set 10 seconds timeout\n");
		timeout = g_timeout_add_seconds(10, (GSourceFunc) pixbuf_cache_timeout_passed, NULL);
	}
}
