addrbook_add_attrib_list( AddressBookFile *book, ItemPerson *person, GList *listAttrib ) {
	GList *node;

	cm_return_if_fail( book != NULL );
	cm_return_if_fail( person != NULL );

   	node = listAttrib;
	while( node ) {
		UserAttribute *attrib = node->data;
		if( attrib->uid == NULL ) {
			addrcache_id_attribute( book->addressCache, attrib );
		}
		addritem_person_add_attribute( person, attrib );
		node = g_list_next( node );
	}
	addrcache_set_dirty( book->addressCache, TRUE );
}
