preferences_response_cb(GtkWidget *dialog, gint response, gpointer data)
{
	if (response == GTK_RESPONSE_HELP) {
		GError *error = NULL;
		gtk_show_uri (gtk_widget_get_screen (GTK_WIDGET (dialog)),
				"ghelp:stickynotes_applet?stickynotes-advanced-settings",
				gtk_get_current_event_time (),
				&error);
		if (error) {
			dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
								   _("There was an error displaying help: %s"), error->message);
			g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(gtk_widget_destroy), NULL);
			gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
			gtk_window_set_screen (GTK_WINDOW(dialog), gtk_widget_get_screen(GTK_WIDGET(dialog)));
			gtk_widget_show(dialog);
			g_error_free(error);
		}
	}

	else if (response == GTK_RESPONSE_CLOSE)
	        gtk_widget_hide(GTK_WIDGET(dialog));
}
