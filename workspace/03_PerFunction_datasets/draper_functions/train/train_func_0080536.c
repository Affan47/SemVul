on_gm_preferences_dialog_check_button_alt_editor_clicked(
		GtkButton *button, gpointer user_data) {
	gboolean active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));

	if (!active) {
		gtk_entry_set_text(GTK_ENTRY(gm_preferences_dialog_widget(
				"entry_alt_editor")), "");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
				gm_preferences_dialog_widget("check_button_embed_editor")),
				FALSE);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
				gm_preferences_dialog_widget("check_button_needs_terminal")),
				FALSE);
	}

	gm_options_set_int(gm_app_options(gm_app_instance()), "editor_alternative",
				active);

	gtk_widget_set_sensitive(gm_preferences_dialog_widget(
			"entry_alt_editor"), active);
	gtk_widget_set_sensitive(gm_preferences_dialog_widget(
			"check_button_embed_editor"), active);
	gtk_widget_set_sensitive(gm_preferences_dialog_widget(
			"check_button_needs_terminal"),	active);
}
