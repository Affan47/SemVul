addritem_group_add_email( ItemGroup *group, ItemEMail *email ) {
	GList *node;

	cm_return_val_if_fail( group != NULL, FALSE );
	cm_return_val_if_fail( email != NULL, FALSE );

	node = group->listEMail;
	while( node ) {
		if( node->data == email ) return FALSE;
		node = g_list_next( node );
	}
	group->listEMail = g_list_append( group->listEMail, email );
	return TRUE;
}
