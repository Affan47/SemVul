on_delete_share_clicked (GtkWidget *widget, gpointer data)
{
	GtkWidget        *table, *dialog;
	GtkTreeSelection *selection;
	GtkTreeModel     *model;
	GtkTreeIter       iter;
	gint              response;
	OobsList         *list;
	OobsListIter     *list_iter;
	OobsShare        *share;

	table = gst_dialog_get_widget (tool->main_dialog, "shares_table");
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (table));

	if (!gtk_tree_selection_get_selected (selection, &model, &iter))
		return;

	dialog = gtk_message_dialog_new (GTK_WINDOW (tool->main_dialog),
					 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_MESSAGE_WARNING,
					 GTK_BUTTONS_NONE,
					 _("Are you sure you want to delete this share?"));
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
						  _("Other computers in your network will stop viewing this."));
	gtk_dialog_add_buttons (GTK_DIALOG (dialog),
				GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				GTK_STOCK_DELETE, GTK_RESPONSE_ACCEPT,
				NULL);

	gst_dialog_add_edit_dialog (tool->main_dialog, dialog);

	response = gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

	gst_dialog_remove_edit_dialog (tool->main_dialog, dialog);

	if (response == GTK_RESPONSE_ACCEPT) {
		gtk_tree_model_get (model, &iter,
				    COL_SHARE, &share,
				    COL_ITER, &list_iter,
				    -1);

		if (OOBS_IS_SHARE_NFS (share)) {
			list = oobs_nfs_config_get_shares OOBS_NFS_CONFIG ((GST_SHARES_TOOL (tool)->nfs_config));
			oobs_list_remove (list, list_iter);
			gst_tool_commit (tool, GST_SHARES_TOOL (tool)->nfs_config);
		} else {
			list = oobs_smb_config_get_shares OOBS_SMB_CONFIG ((GST_SHARES_TOOL (tool)->smb_config));
			oobs_list_remove (list, list_iter);
			gst_tool_commit (tool, GST_SHARES_TOOL (tool)->smb_config);
		}

		gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
		oobs_list_iter_free (list_iter);
		g_object_unref (share);
	}
}
