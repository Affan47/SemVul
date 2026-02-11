timeout_unmount(gpointer data)
{
	char *mount_dir = (char*)data;

	if (0 != encfs_stash_unmount (mount_dir)) {
		GtkWidget *dialog = gtk_message_dialog_new_with_markup (NULL,
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_ERROR,
				GTK_BUTTONS_CANCEL,
				"<span weight=\"bold\" size=\"larger\">%s</span>",
				_("Forced unmounting of the encrypted folder was not successful"));
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
	free(data);
	return FALSE;
}
