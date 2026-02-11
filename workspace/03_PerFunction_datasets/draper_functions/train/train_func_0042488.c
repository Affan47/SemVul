edit_person_email_list_selected( GtkCMCList *clist, gint row, gint column, GdkEvent *event, gpointer data ) {
	ItemEMail *email = gtk_cmclist_get_row_data( clist, row );
	if( email ) {
		if( email->address )
			gtk_entry_set_text( GTK_ENTRY(personeditdlg.entry_email), email->address );
		if( ADDRITEM_NAME(email) )
			gtk_entry_set_text( GTK_ENTRY(personeditdlg.entry_alias), ADDRITEM_NAME(email) );
		if( email->remarks )
			gtk_entry_set_text( GTK_ENTRY(personeditdlg.entry_remarks), email->remarks );
		if (!personeditdlg.read_only) {
			gtk_widget_set_sensitive(personeditdlg.email_del, TRUE);
			gtk_widget_set_sensitive(personeditdlg.email_up, row > 0);
			gtk_widget_set_sensitive(personeditdlg.email_down, gtk_cmclist_get_row_data(clist, row + 1) != NULL);
		}
	} else {
		gtk_widget_set_sensitive(personeditdlg.email_del, FALSE);
		gtk_widget_set_sensitive(personeditdlg.email_up, FALSE);
		gtk_widget_set_sensitive(personeditdlg.email_down, FALSE);
	}
	personeditdlg.rowIndEMail = row;
	edit_person_status_show( NULL );
}
