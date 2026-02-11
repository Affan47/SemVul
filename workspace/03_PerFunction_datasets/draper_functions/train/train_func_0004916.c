draw_phase(Miniscope *m)
{
	GtkWidget *widget;
	GdkSegment seg;
	gint x, y, w, h, d;

	widget = GTK_WIDGET(m);

	w = widget->allocation.width;
	h = widget->allocation.height;

	gdk_draw_rectangle(m->pixmap,
			   widget->style->black_gc, TRUE,
			   0, 0, w, h);

	d = 0.9 * MIN(w, h);
	x = w / 2 - d / 2;
	y = h / 2 - d / 2;

	gdk_draw_arc(m->pixmap,
		     m->green_gc, FALSE,
		     x, y, d, d, 0, 360 * 64);

	seg.x1 = w / 2;
	seg.y1 = h / 2;
	seg.x2 = seg.x1 + 0.4 * d * cos(m->phase - M_PI_2);
	seg.y2 = seg.y1 + 0.4 * d * sin(m->phase - M_PI_2);

	if (m->highlight)
		gdk_draw_segments(m->pixmap, m->yellow_gc, &seg, 1);
	else
		gdk_draw_segments(m->pixmap, m->green_gc, &seg, 1);

	gdk_draw_pixmap(widget->window,
			widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
			m->pixmap,
			0, 0,
			0, 0,
			w, h);
}
