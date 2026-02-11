hslider_expose(
	GtkWidget *widget, GdkRectangle *rect, gdouble sliderstate, GdkPixbuf *image,
	gdouble sat, gboolean has_focus, gboolean paint_focus)
{
	gint slider_width;
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	GdkPixbuf *image1 = gdk_pixbuf_copy(image);
	gdk_pixbuf_copy_area(image, rect->width, 0, slider_width, rect->height, image1, (int)(sliderstate), 0);
	if (has_focus) {
		gdk_pixbuf_saturate_and_pixelate(image1, image1, sat, FALSE);
		if (paint_focus) {
			gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
			                rect->x, rect->y, rect->width, rect->height);
		}
	}
	cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(widget));
	gdk_cairo_set_source_pixbuf (cr, image1, rect->x, rect->y);
	cairo_rectangle(cr, rect->x, rect->y, rect->width, rect->height);
	cairo_fill(cr);
	cairo_destroy (cr);
	g_object_unref(image1);
}
