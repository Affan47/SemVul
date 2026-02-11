theme_notify_func (GConfClient *client,
		   guint cnxn_id,
		   GConfEntry *entry,
		   gpointer user_data)
{
	GtkWidget *dialog;
	GConfValue *value;
	value = gconf_entry_get_value (entry);
	gc_theme = g_strdup_printf ("%s%s%s", PKGDATA_DIR, "/themes/", gconf_value_get_string (value));
	gm_debug ("theme changed\n");

	if (!g_file_test (gc_theme, G_FILE_TEST_EXISTS)) {
		dialog = gtk_message_dialog_new_with_markup (GTK_WINDOW (window),
							     GTK_DIALOG_DESTROY_WITH_PARENT,
							     GTK_MESSAGE_WARNING,
							     GTK_BUTTONS_OK,
							     _("<span size=\"medium\" weight=\"bold\">Unable to load theme!</span>\n\n"
							       "<i>'%s'</i> does not exist!!\n\n"
							       "Default theme will be loaded instead."), gc_theme);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		gconf_client_set_string (settings, "/apps/gnome-mastermind/theme", "simple.svg", NULL);
		gc_theme = g_strdup_printf ("%s%s", PKGDATA_DIR, "/themes/simple.svg");
	}

	old_xpos = xpos;
	old_ypos = ypos;
	selectedcolor = -1;
	gtk_widget_queue_resize (drawing_area);
}
