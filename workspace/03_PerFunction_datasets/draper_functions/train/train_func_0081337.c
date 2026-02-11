style_data_set_font (StyleData * sdata, const gchar *font)
{
	PangoFontDescription *desc;
	const gchar *font_family;

	g_return_if_fail (sdata);

	desc = pango_font_description_from_string (font);
	font_family = pango_font_description_get_family(desc);
	string_assign (&sdata->font, font_family);


	if (sdata->font)
	{
		gchar *s = sdata->font;
		while(*s)
		{
			*s = tolower(*s);
			s++;
		}
	}
	pango_font_description_free (desc);
}
