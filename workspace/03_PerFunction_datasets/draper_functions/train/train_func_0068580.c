edit_group_load_clist( GtkCMCList *clist, GList *listEMail ) {
	GList *node = listEMail;
	gtk_cmclist_freeze(clist);
	while( node ) {
		ItemEMail *email = node->data;
		edit_group_clist_add_email( clist, email );
		node = g_list_next( node );
	}
	gtk_cmclist_thaw(clist);
}
