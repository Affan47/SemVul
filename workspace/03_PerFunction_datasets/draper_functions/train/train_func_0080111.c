on_subversion_remove_response(GtkDialog* dialog, gint response,
							  SubversionData* data)
{
	switch (response)
	{
		case GTK_RESPONSE_OK:
		{
			GtkWidget* fileentry = GTK_WIDGET (gtk_builder_get_object (data->bxml, "remove_path_entry"));
			GtkWidget* force = GTK_WIDGET (gtk_builder_get_object (data->bxml, "subversion_force"));
			GtkWidget *remove_log_view;
			const gchar* filename = gtk_entry_get_text(GTK_ENTRY(fileentry));
			gchar *log;
			SvnRemoveCommand *remove_command;

			remove_log_view = GTK_WIDGET (gtk_builder_get_object (data->bxml,
													"remove_log_view"));
			log = get_log_from_textview (remove_log_view);

			if (!check_input (GTK_WIDGET (dialog),
							  fileentry, _("Please enter a path.")))
			{
				break;
			}


			remove_command = svn_remove_command_new_path ((gchar *) filename, log,
														  gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (force)));

			g_signal_connect (G_OBJECT (remove_command), "command-finished",
							  G_CALLBACK (on_remove_command_finished),
							  data->plugin);

			anjuta_command_start (ANJUTA_COMMAND (remove_command));

			subversion_data_free(data);
			gtk_widget_destroy (GTK_WIDGET(dialog));
			break;
		}
		default:
		{
			subversion_data_free(data);
			gtk_widget_destroy (GTK_WIDGET(dialog));
		}
	}
}
