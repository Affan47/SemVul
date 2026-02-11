gm_preferences_dialog_update_color_buttons(gboolean signals) {
	GmKeyValuePair const *pair;
	GtkColorButton *but;
	GdkColor col;
	GmColorTable *color_table = gm_app_color_table(gm_app_instance());

	for (pair = color_mapping; pair->key != NULL; ++pair) {
		but = GTK_COLOR_BUTTON(gm_preferences_dialog_widget(pair->key));

		gm_color_table_get(color_table, pair->value, &col);
		gtk_color_button_set_color(but, &col);

		if (signals) {
			g_signal_connect(but, "color-set",
					G_CALLBACK(on_gm_preferences_dialog_color_set),
					pair->value);
		}
	}
}
