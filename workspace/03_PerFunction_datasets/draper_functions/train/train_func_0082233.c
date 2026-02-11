imp_ldif_file_move() {
	gboolean retVal = FALSE;
	gchar *sName;
	gchar *sFile;
	gchar *sMsg = NULL;
	gboolean errFlag = FALSE;

	sFile = gtk_editable_get_chars( GTK_EDITABLE(impldif_dlg.entryFile), 0, -1 );
	g_strchug( sFile ); g_strchomp( sFile );

	sName = gtk_editable_get_chars( GTK_EDITABLE(impldif_dlg.entryName), 0, -1 );
	g_strchug( sName ); g_strchomp( sName );

	g_free( impldif_dlg.nameBook );
	g_free( impldif_dlg.fileName );
	impldif_dlg.nameBook = sName;
	impldif_dlg.fileName = sFile;

	gtk_entry_set_text( GTK_ENTRY(impldif_dlg.entryFile), sFile );
	gtk_entry_set_text( GTK_ENTRY(impldif_dlg.entryName), sName );

	if( *sFile == '\0' ) {
		sMsg = _( "Please select a file." );
		gtk_widget_grab_focus(impldif_dlg.entryFile);
		errFlag = TRUE;
	}

	if( ! errFlag && *sName == '\0' ) {
		sMsg = _( "Address book name must be supplied." );
		gtk_widget_grab_focus(impldif_dlg.entryName);
		errFlag = TRUE;
	}

	if( ! errFlag ) {

		ldif_set_file( _ldifFile_, sFile );
		if( ldif_read_tags( _ldifFile_ ) == MGU_SUCCESS ) {


			imp_ldif_load_fields( _ldifFile_ );
			retVal = TRUE;
		}
		else {
			sMsg = imp_ldif_err2string( _lutErrorsLDIF_, _ldifFile_->retVal );
		}
	}
	imp_ldif_status_show( sMsg );

	return retVal;
}
