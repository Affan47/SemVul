icg_error_error_info_list (GOCmdContext *cc, GSList *error)
{
	GnmIOContextGtk *icg = GNM_IO_CONTEXT_GTK (cc);
	if (icg->show_warnings && error != NULL && error->data != NULL) {
		GtkWidget *dialog = gnumeric_go_error_info_dialog_create
			(error->data);
		gtk_widget_show_all (GTK_WIDGET (dialog));
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
}
