dialog_get_password (gchar *info_message,
			     gchar *password_message, gchar *confirm_message,
			     gchar *distinct_error_message, guint minimum_length)
{
	GObject * widget = NULL, * password_widget = NULL;

	GtkBuilder * dialog_gtkb = NULL;
	gint response = 0;
	gchar *password = NULL;
	const gchar *passwordagain = NULL;

	dialog_gtkb = gtk_builder_new();
	gtk_builder_add_from_file (dialog_gtkb,
				   g_build_filename (PACKAGE_DATA_DIR, "gnomint", "get_password_dialog.ui", NULL ),
				   NULL);
	gtk_builder_connect_signals (dialog_gtkb, NULL);

	widget = gtk_builder_get_object (dialog_gtkb, "info_message");
	gtk_label_set_text (GTK_LABEL(widget), info_message);
	widget = gtk_builder_get_object (dialog_gtkb, "password_message");
	gtk_label_set_text (GTK_LABEL(widget), password_message);
	widget = gtk_builder_get_object (dialog_gtkb, "confirm_message");
	gtk_label_set_text (GTK_LABEL(widget), confirm_message);

	password_widget = gtk_builder_get_object (dialog_gtkb, "password_entry");
	widget = gtk_builder_get_object (dialog_gtkb, "password_dialog_ok_button");
	g_object_set_data (G_OBJECT(password_widget), "minimum_length",
                           GINT_TO_POINTER(minimum_length));
	g_object_set_data (G_OBJECT(password_widget), "ok_button", widget);

	do {
		gtk_widget_grab_focus (GTK_WIDGET(password_widget));

		if (password)
			g_free (password);

		widget = gtk_builder_get_object (dialog_gtkb, "get_password_dialog");
		response = gtk_dialog_run(GTK_DIALOG(widget));

		if (!response) {
			gtk_widget_destroy (GTK_WIDGET(widget));
			g_object_unref (G_OBJECT(dialog_gtkb));
			return NULL;
		} else {
			widget = gtk_builder_get_object (dialog_gtkb, "password_entry");
			password = g_strdup(gtk_entry_get_text (GTK_ENTRY(widget)));
			widget = gtk_builder_get_object (dialog_gtkb, "confirm_entry");
			passwordagain = gtk_entry_get_text (GTK_ENTRY(widget));
		}

		if (strcmp (password, passwordagain)) {
			dialog_error (distinct_error_message);
		}

	} while (strcmp (password, passwordagain));

	widget = gtk_builder_get_object (dialog_gtkb, "get_password_dialog");
	gtk_widget_destroy (GTK_WIDGET(widget));
	g_object_unref (G_OBJECT(dialog_gtkb));

	return password;
}
