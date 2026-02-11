addrcache_hash_add_folder( AddressCache *cache, ItemFolder *folder ) {
	cm_return_val_if_fail( cache != NULL, FALSE );
	cm_return_val_if_fail( folder != NULL, FALSE );

	if( g_hash_table_lookup( cache->itemHash, ADDRITEM_ID(folder) ) ) {
		return FALSE;
	}
	g_hash_table_insert( cache->itemHash, ADDRITEM_ID(folder), folder );
	return TRUE;
}
