open_ok_cb (GtkWidget *widget, gpointer user_data)
{
	Alleyoop *grind = user_data;
	const char *filename;
	GtkWidget *filesel;
	int fd;

	filesel = g_object_get_data ((GObject *) grind, "open_filesel");
	filename = gtk_file_selection_get_filename ((GtkFileSelection *) filesel);

	if (filename != NULL) {
		if ((fd = open (filename, O_RDONLY)) != -1) {
			vg_tool_view_connect ((VgToolView *) grind->view, fd);

			grind->pid = (pid_t) -1;
			grind->gio = g_io_channel_unix_new (fd);
			grind->watch_id = g_io_add_watch (grind->gio, G_IO_IN | G_IO_HUP, io_ready_cb, grind);

			gtk_widget_set_sensitive (grind->toolbar_run, FALSE);
			gtk_widget_set_sensitive (grind->toolbar_kill, TRUE);
		} else {
			GtkWidget *dialog;

			dialog = gtk_message_dialog_new ((GtkWindow *) grind, GTK_DIALOG_DESTROY_WITH_PARENT,
							 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
							 _("Could not load `%s': %s"), filename,
							 g_strerror (errno));

			g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);

			gtk_widget_show (dialog);
		}
	}

	gtk_widget_destroy (filesel);
}
