addrcache_free_item_vis( gpointer key, gpointer value, gpointer data ) {
	AddrItemObject *obj = ( AddrItemObject * ) value;

	if( ADDRITEM_TYPE(obj) == ITEMTYPE_PERSON ) {
		addritem_free_item_person( ( ItemPerson * ) obj );
	}
	else if( ADDRITEM_TYPE(obj) == ITEMTYPE_EMAIL ) {
		addritem_free_item_email( ( ItemEMail * ) obj );
	}
	else if( ADDRITEM_TYPE(obj) == ITEMTYPE_GROUP ) {
		addritem_free_item_group( ( ItemGroup * ) obj );
	}
	else if( ADDRITEM_TYPE(obj) == ITEMTYPE_FOLDER ) {
		addritem_free_item_folder( ( ItemFolder * ) obj );
	}
	key = NULL;
	value = NULL;
	return TRUE;
}
