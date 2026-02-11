preferences_fonts_font_set_cb (GtkFontButton *button,
                               gpointer       user_data)
{
	DhPreferences *prefs = user_data;
	const gchar   *font_name;
	const gchar   *key;

	font_name = gtk_font_button_get_font_name (button);

	if (GTK_WIDGET (button) == prefs->variable_font_button) {
		key = DH_CONF_VARIABLE_FONT;
	} else {
		key = DH_CONF_FIXED_FONT;
	}

	ige_conf_set_string (ige_conf_get (), key, font_name);
}
