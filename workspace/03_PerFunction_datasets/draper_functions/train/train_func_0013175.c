style_font_read_from_x11 (GnmStyle *mstyle, char const *fontname)
{
	char const *c;


	c = font_component (fontname, 2);
	if (strncmp (c, "bold", 4) == 0)
		gnm_style_set_font_bold (mstyle, TRUE);

	c = font_component (fontname, 3);
	if (strncmp (c, "o", 1) == 0)
		gnm_style_set_font_italic (mstyle, TRUE);

	if (strncmp (c, "i", 1) == 0)
		gnm_style_set_font_italic (mstyle, TRUE);
}
