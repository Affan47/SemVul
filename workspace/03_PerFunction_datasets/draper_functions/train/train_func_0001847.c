ldapqry_free_list_name_value( GList *list ) {
	GList *node;

	node = list;
	while( node ) {
		NameValuePair *nvp = ( NameValuePair * ) node->data;
		ldapqry_free_name_value( nvp );
		node->data = NULL;
		node = g_list_next( node );
	}
	g_list_free( list );
}
