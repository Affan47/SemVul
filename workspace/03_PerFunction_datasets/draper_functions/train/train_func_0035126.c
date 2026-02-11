gx_vslider_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_VSLIDER(widget));
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb) - slider_height;
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.height-slider_height);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	vslider_expose(widget, &image_rect, sliderstate, pb, sat, TRUE, FALSE);
	g_object_unref(pb);
	return TRUE;
}
