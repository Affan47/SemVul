pixbuf_cache_destroy(void)
{
	g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Destroy pixbuf cache");
	if (timeout > 0)
		g_source_remove(timeout);
	timeout = 0;
	g_hash_table_destroy(pb_cache);
	pb_cache = NULL;
	g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG,"remaining size: %u\n", total_size);
}
