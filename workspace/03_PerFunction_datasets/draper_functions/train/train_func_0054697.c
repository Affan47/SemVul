addrcache_get_all_persons( AddressCache *cache ) {
	GList *list = NULL;

	cm_return_val_if_fail( cache != NULL, NULL );

	cache->tempList = NULL;
	g_hash_table_foreach( cache->itemHash, addrcache_get_all_persons_vis, cache );
	list = cache->tempList;
	cache->tempList = NULL;
	return list;
}
