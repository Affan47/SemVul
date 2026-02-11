pgd_attachments_save_button_clicked (GtkButton   *button,
				     GtkTreeView *treeview)
{
	GtkTreeSelection  *selection;
	GtkTreeModel      *model;
	GtkTreeIter        iter;
	GtkWidget         *file_chooser;
	PopplerAttachment *attachment;

	selection = gtk_tree_view_get_selection (treeview);
	if (!gtk_tree_selection_get_selected (selection, &model, &iter))
		return;

	gtk_tree_model_get (model, &iter,
			    ATTACHMENTS_ATTACHMENT_COLUMN, &attachment,
			    -1);

	if (!attachment)
		return;

	file_chooser = gtk_file_chooser_dialog_new ("Save attachment",
						    GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
						    GTK_FILE_CHOOSER_ACTION_SAVE,
						    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						    GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
						    NULL);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (file_chooser), attachment->name);
	g_signal_connect (G_OBJECT (file_chooser), "response",
			  G_CALLBACK (pgd_attachments_save_dialog_response),
			  (gpointer) attachment);
	gtk_widget_show (file_chooser);

}
