export_html_cancel( GtkWidget *widget, gpointer data ) {
	gint pageNum;

	pageNum = gtk_notebook_get_current_page( GTK_NOTEBOOK(exphtml_dlg.notebook) );
	if( pageNum != PAGE_FINISH ) {
		exphtml_dlg.cancelled = TRUE;
	}
	gtk_main_quit();
}
