goc_text_draw (GocItem const *item, cairo_t *cr)
{
	GocText *text = GOC_TEXT (item);
	double x = (goc_canvas_get_direction (item->canvas) == GOC_DIRECTION_RTL)? text->x + text->w: text->x,
	       y = text->y, dx = 0., dy = 0., h, w;
	double sign = (goc_canvas_get_direction (item->canvas) == GOC_DIRECTION_RTL)? -1.: 1.;

	PangoLayout *pl;
	GOStyle *style = go_styled_object_get_style (GO_STYLED_OBJECT (item));
	if (!text->text)
		return;
	w = (text->clip_width > 0.)? MIN (text->clip_width, text->w): text->w;
	h = (text->clip_height > 0.)? MIN (text->clip_height, text->h): text->h;
	pl = pango_cairo_create_layout (cr);
	pango_layout_set_font_description (pl, style->font.font->desc);
	pango_layout_set_text (pl, text->text, -1);
	if (text->wrap_width > 0) {
		pango_layout_set_width (pl, text->wrap_width * PANGO_SCALE);
		pango_layout_set_wrap (pl, PANGO_WRAP_WORD_CHAR);
	}
	if (text->attributes)
		pango_layout_set_attributes (pl, text->attributes);

	switch (text->anchor) {
	case GO_ANCHOR_CENTER:
	case GO_ANCHOR_NORTH:
	case GO_ANCHOR_SOUTH:
		dx = -w / 2.;
		break;
	case GO_ANCHOR_NORTH_WEST:
	case GO_ANCHOR_SOUTH_WEST:
	case GO_ANCHOR_WEST:
		break;
	case GO_ANCHOR_NORTH_EAST:
	case GO_ANCHOR_SOUTH_EAST:
	case GO_ANCHOR_EAST:
		dx = -w;
		break;
	default:
		break;
	}

	switch (text->anchor) {
	case GO_ANCHOR_NORTH:
	case GO_ANCHOR_NORTH_WEST:
	case GO_ANCHOR_NORTH_EAST:
		break;
	case GO_ANCHOR_CENTER:
	case GO_ANCHOR_WEST:
	case GO_ANCHOR_EAST:
		dy = -h / 2.;
		break;
	case GO_ANCHOR_SOUTH:
	case GO_ANCHOR_SOUTH_WEST:
	case GO_ANCHOR_SOUTH_EAST:
		dy = -h;
		break;
	default:
		break;
	}
	cairo_save (cr);
	_goc_item_transform (item, cr, TRUE);
	cairo_set_source_rgb (cr, 0., 0., 0.);
	goc_group_cairo_transform (item->parent, cr, x, y);
	cairo_rotate (cr, text->rotation * sign);
	cairo_translate (cr, dx, dy);
	cairo_rectangle (cr, 0., 0., w, h);
	cairo_clip (cr);
	pango_cairo_show_layout (cr, pl);
	cairo_new_path (cr);
	cairo_restore (cr);
	g_object_unref (pl);
}
