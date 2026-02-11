gtk_hex_draw (GtkWidget *w,
              cairo_t *cr)
{
	if (GTK_WIDGET_CLASS (parent_class)->draw)
		(* GTK_WIDGET_CLASS (parent_class)->draw) (w, cr);

	draw_shadow (w, cr);

	return TRUE;
}
