exp_ldif_file_select_create( AddressFileSelection *afs ) {
	gchar *file = filesel_select_file_save(_("Select LDIF output file"), NULL);

	if (file == NULL)
		afs->cancelled = TRUE;
	else {
		afs->cancelled = FALSE;
		gtk_entry_set_text( GTK_ENTRY(expldif_dlg.entryLdif), file );
		g_free(file);
	}
}
