addressDialClicked( gpointer pData, GtkWidget *psWidget ) {
	GtkWidget *psEntry = GTK_WIDGET( pData );
	gint nType = GPOINTER_TO_INT( g_object_get_data( G_OBJECT( psAddressBook ), "type" ) );
	GtkWidget *psParent = g_object_get_data( G_OBJECT( psAddressBook ), "parent" );
	const gchar *pnNumber = gtk_entry_get_text( GTK_ENTRY( psEntry ) );
	struct sPerson *psPerson = findPersonByNumber( pnNumber );

	if ( psPerson != NULL ) {
		if ( psParent != NULL && nType == 1 ) {
			setDialNameNumber( psParent, psPerson -> pnDisplayName, pnNumber );
			gtk_widget_destroy( GTK_WIDGET( psAddressBook ) );
			psAddressBook = NULL;
		} else {
			dialNumberDialog( psPerson, pnNumber );
		}
	}
}
