cd_sample_widget_draw (GtkWidget *widget, cairo_t *cr)
{
	CdColorRGB *color;
	CdSampleWidget *sample = CD_SAMPLE_WIDGET (widget);
	GtkAllocation allocation;

	g_return_val_if_fail (CD_IS_SAMPLE_WIDGET (sample), FALSE);

	color = &sample->priv->color;
	gtk_widget_get_allocation (widget, &allocation);
	cairo_save (cr);
	cairo_set_source_rgb (cr, color->R, color->G, color->B);
	cd_sample_widget_draw_rounded_rectangle (cr, 0, 0,
						 allocation.width,
						 allocation.height,
						 10.5);
	cairo_fill_preserve (cr);
	cairo_set_source_rgba (cr, 0.5, 0.5, 0.5, 1.0);
	cairo_set_line_width (cr, 1.0);
	cairo_stroke (cr);
	cairo_restore (cr);
	return FALSE;
}
