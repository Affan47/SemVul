gx_knob_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_KNOB(widget));
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	if (GDK_IS_PIXBUF (pb)) {
		gint fcount;
		get_image_dimensions (widget, pb, &image_rect, &fcount);
		gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
		_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
		_gx_knob_expose(widget, &image_rect, knobstate, pb, fcount, gtk_widget_has_focus(widget));
		_gx_regler_display_value(GX_REGLER(widget), &value_rect);
		g_object_unref(pb);
	}
	return FALSE;
}
