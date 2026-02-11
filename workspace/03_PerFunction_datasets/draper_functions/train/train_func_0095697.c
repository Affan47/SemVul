check_group_delete (OobsGroup *group)
{
	GtkWidget *parent;
	GtkWidget *dialog;
	gint reply;

	parent = gst_dialog_get_widget (tool->main_dialog, "group_settings_dialog");

	if (oobs_group_get_gid (group) == 0) {
		dialog = gtk_message_dialog_new (GTK_WINDOW (parent),
						 GTK_DIALOG_MODAL,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 _("Administrator group can not be deleted"));

		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
							  _("This would leave the system unusable."));
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);

		return FALSE;
	}


	dialog = gtk_message_dialog_new (GTK_WINDOW (parent),
					 GTK_DIALOG_MODAL,
					 GTK_MESSAGE_WARNING,
					 GTK_BUTTONS_NONE,
					 _("Are you sure you want to delete group \"%s\"?"),
					 oobs_group_get_name (group));
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
						  _("This may leave files with invalid group ID in the filesystem."));
	gtk_dialog_add_buttons (GTK_DIALOG (dialog),
				GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				GTK_STOCK_DELETE, GTK_RESPONSE_ACCEPT,
				NULL);

	gst_dialog_add_edit_dialog (tool->main_dialog, dialog);
	reply = gtk_dialog_run (GTK_DIALOG (dialog));
	gst_dialog_remove_edit_dialog (tool->main_dialog, dialog);

	gtk_widget_destroy (dialog);

	return (reply == GTK_RESPONSE_ACCEPT);
}
