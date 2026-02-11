gnome_canvas_rect_setup_for_stroke (GnomeCanvasRect *rect,
                                    cairo_t *cr)
{
	if (!rect->priv->outline_set)
		return FALSE;

	cairo_set_source_rgba (
		cr,
		((rect->priv->outline_rgba >> 24) & 0xff) / 255.0,
		((rect->priv->outline_rgba >> 16) & 0xff) / 255.0,
		((rect->priv->outline_rgba >>  8) & 0xff) / 255.0,
		( rect->priv->outline_rgba        & 0xff) / 255.0);
	cairo_set_line_width (cr, rect->priv->line_width);
	cairo_set_line_cap (cr, rect->priv->cap);
	cairo_set_line_join (cr, rect->priv->join);
	cairo_set_miter_limit (cr, rect->priv->miterlimit);
	cairo_set_dash (
		cr, rect->priv->dash, rect->priv->n_dash,
		rect->priv->dash_offset);

	return TRUE;
}
