profilesToXmlnode( void ) {
	xmlnode *node, *child;
	GList *cur;

	node = xmlnode_new( "profile" );
	xmlnode_set_attrib( node, "version", "1.0" );

	for ( cur = getProfiles(); cur != NULL; cur = cur -> next ) {
		child = profileToXmlnode( cur -> data );
		xmlnode_insert_child( node, child );
	}

	if ( psActiveProfile != NULL ) {
		child = xmlnode_new_child( node, "active" );
		xmlnode_insert_data( child, psActiveProfile -> pnName, -1 );
	}

	return node;
}
