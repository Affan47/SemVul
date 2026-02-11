addrcache_id_attribute( AddressCache *cache, UserAttribute *attrib ) {
	cm_return_if_fail( cache != NULL );
	cm_return_if_fail( attrib != NULL );
	if( attrib->uid ) return;
	addrcache_next_id( cache );
	attrib->uid = g_strdup_printf( "%d", cache->nextID );
}
