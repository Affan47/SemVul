ldapsvr_free_all_query( LdapServer *server ) {
	GList *node;
	cm_return_if_fail( server != NULL );

	node = server->listQuery;
	while( node ) {
		LdapQuery *qry = node->data;
		ldapqry_free( qry );
		node->data = NULL;
		node = g_list_next( node );
	}
	g_list_free( server->listQuery );
	server->listQuery = NULL;
}
