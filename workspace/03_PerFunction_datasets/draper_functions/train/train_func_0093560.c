addrcache_get_object( AddressCache *cache, const gchar *uid ) {
	AddrItemObject *obj = NULL;
	gchar *uidH;

	cm_return_val_if_fail( cache != NULL, NULL );

	if( uid == NULL || *uid == '\0' ) return NULL;
	obj = ( AddrItemObject * ) g_hash_table_lookup( cache->itemHash, uid );
	if( obj ) {

		uidH = ADDRITEM_ID(obj);
		if( uidH ) {
			if( strcmp( uidH, uid ) == 0 ) return obj;
		}
	}
	return NULL;
}
