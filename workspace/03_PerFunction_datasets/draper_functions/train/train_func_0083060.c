ldapsvr_stop_all_query( LdapServer *server ) {
	GList *node;
	cm_return_if_fail( server != NULL );

	node = server->listQuery;
	while( node ) {
		LdapQuery *qry = node->data;
		ldapqry_set_stop_flag( qry, TRUE );
		node = g_list_next( node );
	}
}
