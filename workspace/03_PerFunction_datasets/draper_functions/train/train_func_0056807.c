msgcache_destroy(MsgCache *cache)
{
	cm_return_if_fail(cache != NULL);

	g_hash_table_foreach_remove(cache->msgnum_table, msgcache_msginfo_free_func, NULL);
	g_hash_table_destroy(cache->msgid_table);
	g_hash_table_destroy(cache->msgnum_table);
	g_free(cache);
}
