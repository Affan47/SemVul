richText(char *txt,int len,int x,int y,int w,int h,int align)
{
	PangoLayout *ly;
	char *html;

	if (!txt || !len) return;

	ly = pango_layout_new(ft->ct);
	if (w > 0)
		pango_layout_set_width(ly, w * PANGO_SCALE);
	html = gt_html_to_pango_string(txt, len, false);
	pango_layout_set_markup(ly, html, -1);
	pango_layout_set_wrap(ly, PANGO_WRAP_WORD_CHAR);
	drawLayout(ly, true, x, y, w, h, align);
	g_free(html);
}
