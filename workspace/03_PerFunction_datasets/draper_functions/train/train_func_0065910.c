imp_ldif_prev( GtkWidget *widget ) {
	gint pageNum;

	pageNum = gtk_notebook_get_current_page( GTK_NOTEBOOK(impldif_dlg.notebook) );
	if( pageNum == PAGE_ATTRIBUTES ) {

		gtk_notebook_set_current_page(
			GTK_NOTEBOOK(impldif_dlg.notebook), PAGE_FILE_INFO );
		gtk_widget_set_sensitive( impldif_dlg.btnPrev, FALSE );
		gtk_widget_hide( impldif_dlg.btnProceed );
		gtk_widget_show( impldif_dlg.btnNext );
	}
	imp_ldif_message();
}
