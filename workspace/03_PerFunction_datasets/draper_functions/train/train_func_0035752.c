edit_person_email_delete( gpointer data ) {
	GtkCMCList *clist = GTK_CMCLIST(personeditdlg.clist_email);
	gint row = personeditdlg.rowIndEMail;
	ItemEMail *email = gtk_cmclist_get_row_data( clist, row );
	edit_person_email_clear( NULL );
	if( email ) {

		gtk_cmclist_remove( clist, row );
		addritem_free_item_email( email );
		email = NULL;
	}


	email = gtk_cmclist_get_row_data( clist, row );
	if( ! email ) {
		personeditdlg.rowIndEMail = -1 + row;
	}
	if (!personeditdlg.read_only) {
		gtk_widget_set_sensitive(personeditdlg.email_del, gtk_cmclist_get_row_data(clist, 0) != NULL);
		gtk_widget_set_sensitive(personeditdlg.email_up, gtk_cmclist_get_row_data(clist, personeditdlg.rowIndEMail + 1) != NULL);
		gtk_widget_set_sensitive(personeditdlg.email_down, gtk_cmclist_get_row_data(clist, personeditdlg.rowIndEMail - 1) != NULL);
	}
	edit_person_status_show( NULL );
}
