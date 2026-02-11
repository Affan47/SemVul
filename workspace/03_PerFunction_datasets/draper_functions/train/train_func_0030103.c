draw_stretch_handles (NemoIconCanvasItem *item,
                      cairo_t *cr,
		      const EelIRect *rect)
{
	GtkWidget *widget;
	GdkPixbuf *knob_pixbuf;
	int knob_width, knob_height;
	double dash = { 2.0 };
	GtkStyleContext *style;
	GdkRGBA color;

	if (!item->details->show_stretch_handles) {
		return;
	}

	widget = GTK_WIDGET (EEL_CANVAS_ITEM (item)->canvas);
	style = gtk_widget_get_style_context (widget);

        cairo_save (cr);
	knob_pixbuf = get_knob_pixbuf ();
	knob_width = gdk_pixbuf_get_width (knob_pixbuf);
	knob_height = gdk_pixbuf_get_height (knob_pixbuf);


	gtk_style_context_get_color (style, GTK_STATE_FLAG_SELECTED, &color);
	gdk_cairo_set_source_rgba (cr, &color);
	cairo_set_dash (cr, &dash, 1, 0);
	cairo_set_line_width (cr, 1.0);
	cairo_rectangle (cr,
			 rect->x0 + 0.5,
			 rect->y0 + 0.5,
			 rect->x1 - rect->x0 - 1,
			 rect->y1 - rect->y0 - 1);
	cairo_stroke (cr);

        cairo_restore (cr);


	draw_pixbuf (knob_pixbuf, cr, rect->x0, rect->y0);
	draw_pixbuf (knob_pixbuf, cr, rect->x0, rect->y1 - knob_height);
	draw_pixbuf (knob_pixbuf, cr, rect->x1 - knob_width, rect->y0);
	draw_pixbuf (knob_pixbuf, cr, rect->x1 - knob_width, rect->y1 - knob_height);

	g_object_unref (knob_pixbuf);
}
