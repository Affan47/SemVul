searchWindow( GtkWidget *psButton, gpointer pUserData ) {
	GtkWidget *psDialog = pUserData;
	GtkWidget *psExecEntry = g_object_get_data( G_OBJECT( psDialog ), "exec_entry" );
	GtkWidget *psChooser = gtk_file_chooser_dialog_new( _( "Select programm" ), GTK_WINDOW( psDialog ), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL );
	gint nResult = 0;

	nResult = gtk_dialog_run( GTK_DIALOG( psChooser ) );
	if ( nResult == GTK_RESPONSE_ACCEPT ) {
		gchar *pnFileName;

		pnFileName = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( psChooser ) );
		gtk_entry_set_text( GTK_ENTRY( psExecEntry ), pnFileName );

		g_free( pnFileName );
	}

	gtk_widget_destroy( GTK_WIDGET( psChooser ) );
}
