settings_get_font_desc (GtkSettings *settings)
{
	PangoFontDescription *font_desc;
	char *font_str;

	g_object_get (settings, "gtk-font-name", &font_str, NULL);
	font_desc = pango_font_description_from_string (
		font_str ? font_str : "sans 10");
	g_free (font_str);

	return font_desc;
}
