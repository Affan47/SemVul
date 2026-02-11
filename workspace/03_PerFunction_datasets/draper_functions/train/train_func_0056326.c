_gtk_ok_dialog_with_checkbutton_new (GtkWindow        *parent,
				     GtkDialogFlags    flags,
				     const char       *message,
				     const char       *ok_button_text,
				     const char       *check_button_label,
				     GSettings        *settings,
				     const char       *key)
{
	GtkWidget		*d;
	GtkBuilder              *builder;
	GtkWidget		*check_button;
	DialogWithButtonData	*data;

	d = _gtk_message_dialog_new (parent,
				     flags,
				     GTK_STOCK_DIALOG_INFO,
				     message,
				     NULL,
				     ok_button_text, GTK_RESPONSE_OK,
				     NULL);
	gtk_dialog_set_default_response (GTK_DIALOG (d), GTK_RESPONSE_OK);


	builder = g_object_get_data (G_OBJECT (d), "builder");
	check_button = _gtk_builder_get_widget(builder, "message_checkbutton");
	gtk_container_add (GTK_CONTAINER (check_button), gtk_label_new_with_mnemonic (check_button_label));
	gtk_widget_show_all (check_button);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_button), g_settings_get_boolean (settings, key));

	data = g_new0 (DialogWithButtonData, 1);
	data->settings = g_object_ref (settings);
	data->key = g_strdup (key);
	g_object_set_data_full (G_OBJECT (d), "settings-data", data, (GDestroyNotify) dialog_with_button_data_free);

	g_signal_connect (G_OBJECT (check_button),
			  "toggled",
			  G_CALLBACK (ok__check_button_toggled_cb),
			  data);

	return d;
}
