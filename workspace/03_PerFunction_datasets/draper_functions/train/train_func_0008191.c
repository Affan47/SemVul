gitg_preferences_dialog_present(GtkWindow *window)
{
	if (!preferences_dialog)
		create_preferences_dialog();

	gtk_window_set_transient_for(GTK_WINDOW(preferences_dialog), window);
	gtk_window_present(GTK_WINDOW(preferences_dialog));

	return preferences_dialog;
}
