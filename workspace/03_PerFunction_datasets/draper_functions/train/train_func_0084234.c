choose_format_dialog_response_cb (GtkWidget          *widget,
				  gint                response,
				  ChooseFormatDialog *dialog)
{
	switch (response)
	{
		case GTK_RESPONSE_HELP:
		{
			gedit_debug_message (DEBUG_PLUGINS, "GTK_RESPONSE_HELP");
			gedit_app_show_help (GEDIT_APP (g_application_get_default ()),
					     GTK_WINDOW (widget),
					     NULL,
					     "gedit-plugins-insert-date-time");
			break;
		}
		case GTK_RESPONSE_OK:
		{
			gchar *the_time;

			gedit_debug_message (DEBUG_PLUGINS, "GTK_RESPONSE_OK");


			if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (dialog->use_list)))
			{
				gint sel_format;

				sel_format = get_format_from_list (dialog->list);
				the_time = get_time (formats[sel_format]);

				g_settings_set_enum (dialog->settings,
						     PROMPT_TYPE_KEY,
						     PROMPT_SELECTED_FORMAT);
				g_settings_set_string (dialog->settings,
						       SELECTED_FORMAT_KEY,
						       formats[sel_format]);
			}
			else
			{
				const gchar *format;

				format = gtk_entry_get_text (GTK_ENTRY (dialog->custom_entry));
				the_time = get_time (format);

				g_settings_set_enum (dialog->settings,
						     PROMPT_TYPE_KEY,
						     PROMPT_CUSTOM_FORMAT);
				g_settings_set_string (dialog->settings,
						       CUSTOM_FORMAT_KEY,
						       format);
			}

			g_return_if_fail (the_time != NULL);

			real_insert_time (dialog->buffer, the_time);
			g_free (the_time);

			gtk_widget_destroy (dialog->dialog);
			break;
		}
		case GTK_RESPONSE_CANCEL:
			gedit_debug_message (DEBUG_PLUGINS, "GTK_RESPONSE_CANCEL");
			gtk_widget_destroy (dialog->dialog);
	}
}
