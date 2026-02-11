update_font()
{
	char *family = THIS->font_family;

	if (!family)
		family = "";

	cairo_select_font_face(CNT, family, THIS->font_slant, THIS->font_weight);
}
