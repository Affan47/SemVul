_gconf_cleaner_error_dialog(GConfCleanerInstance *inst,
			    const gchar          *primary_text,
			    const gchar          *secondary_text,
			    gboolean              is_quit)
{
	GtkWidget *dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW (inst->window),
							       GTK_DIALOG_MODAL,
							       GTK_MESSAGE_ERROR,
							       GTK_BUTTONS_OK,
							       "%s",
							       primary_text);

	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog),
						 "%s",
						 secondary_text);
	g_signal_connect(dialog, "response",
			 G_CALLBACK (gtk_widget_destroy), NULL);

	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL, TRUE);

	gtk_dialog_run(GTK_DIALOG (dialog));

	if (is_quit)
		gtk_main_quit();
}
