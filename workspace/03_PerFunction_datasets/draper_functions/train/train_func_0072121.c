addritem_free_item_email( ItemEMail *item ) {
	cm_return_if_fail( item != NULL );


	g_free( ADDRITEM_ID(item) );
	g_free( ADDRITEM_NAME(item) );
	g_free( item->address );
	g_free( item->remarks );

	ADDRITEM_OBJECT(item)->type = ITEMTYPE_NONE;
	ADDRITEM_ID(item) = NULL;
	ADDRITEM_NAME(item) = NULL;
	ADDRITEM_PARENT(item) = NULL;
	ADDRITEM_SUBTYPE(item) = 0;
	item->address = NULL;
	item->remarks = NULL;
	g_free( item );
}
