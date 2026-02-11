addrselect_item_free( AddrSelectItem *item ) {
	if( item ) {
		g_free( item->uid );
		g_free( item->cacheID );
		item->objectType = ITEMTYPE_NONE;
		item->addressItem = NULL;
		item->uid = NULL;
		item->cacheID = NULL;
	}
	g_free( item );
}
