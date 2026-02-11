popup_quit_dialog(void)
{
  static GtkWidget *dialog;

  if (!dialog) {
    dialog = gtk_message_dialog_new(NULL,
	0,
	GTK_MESSAGE_WARNING,
	GTK_BUTTONS_YES_NO,
	_("Are you sure you want to quit?"));
    setup_dialog(dialog, toplevel);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);

    g_signal_connect(dialog, "response",
	G_CALLBACK(quit_dialog_response), NULL);
    g_signal_connect(dialog, "destroy",
	G_CALLBACK(gtk_widget_destroyed), &dialog);
  }

  gtk_window_present(GTK_WINDOW(dialog));
}
