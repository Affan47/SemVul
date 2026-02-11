gf_font_manager_register_font(GF_FontManager *fm, GF_Font *font)
{
	if (fm->font) {
		GF_Font *a_font = fm->font;
		while (a_font->next) a_font = a_font->next;
		a_font->next = font;
	} else {
		fm->font = font;
	}
	font->ft_mgr = fm;
	if (!font->spans) font->spans = gf_list_new();
	return GF_OK;
}
