get_text_extents(GB_PAINT *d, bool rich, const char *text, int len, GB_EXTENTS *ext, float width)
{
	char *html = NULL;
	PangoLayout *layout;
	CFONT *font;
	PangoRectangle rect;
	float x, y;

	layout = create_pango_layout(d);

	if (rich)
	{
		html = gt_html_to_pango_string(text, len, false);
		pango_layout_set_markup(layout, html, -1);
	}
	else
		pango_layout_set_text(layout, text, len);

	_Font(d, FALSE, (GB_FONT *)&font);
	gt_add_layout_from_font(layout, font->font, d->resolutionY);

	if (width > 0)
		pango_layout_set_width(layout, width * PANGO_SCALE);

	pango_layout_get_extents(layout, &rect, NULL);

	GetCurrentPoint(d, &x, &y);

	ext->x1 = (float)rect.x / PANGO_SCALE + x;
	ext->y1 = (float)rect.y / PANGO_SCALE + y - font->font->ascentF();
	ext->x2 = ext->x1 + (float)rect.width / PANGO_SCALE;
	ext->y2 = ext->y1 + (float)rect.height / PANGO_SCALE;

	g_object_unref(layout);
	if (html) g_free(html);
}
