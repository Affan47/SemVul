_gcr_display_view_draw (GtkWidget *widget, cairo_t *cr)
{
	GdkWindow *window;
	gboolean handled = TRUE;


	if (GTK_WIDGET_CLASS (_gcr_display_view_parent_class)->draw)
		handled = GTK_WIDGET_CLASS (_gcr_display_view_parent_class)->draw (widget, cr);

	window = gtk_text_view_get_window (GTK_TEXT_VIEW (widget), GTK_TEXT_WINDOW_TEXT);
	if (gtk_cairo_should_draw_window (cr, window))
		paint_extras (GCR_DISPLAY_VIEW (widget), cr);

	return handled;
}
