on_term_font_set(GtkFontButton *widget, gpointer user_data)
{
	const gchar *fontbtn = gtk_font_button_get_font_name(widget);

	if (! utils_str_equal(fontbtn, vc->font))
	{
		SETPTR(vc->font, g_strdup(gtk_font_button_get_font_name(widget)));
		vte_apply_user_settings();
	}
}
