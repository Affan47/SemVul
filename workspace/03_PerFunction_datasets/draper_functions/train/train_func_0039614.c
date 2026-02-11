gcm_trc_widget_draw_trc (GtkWidget *trc_widget, cairo_t *cr)
{
	GtkAllocation allocation;

	GcmTrcWidget *trc = (GcmTrcWidget*) trc_widget;
	g_return_if_fail (trc != NULL);
	g_return_if_fail (GCM_IS_TRC_WIDGET (trc));

	cairo_save (cr);


	gtk_widget_get_allocation (trc_widget, &allocation);
	trc->priv->chart_height = allocation.height;
	trc->priv->chart_width = allocation.width;
	trc->priv->x_offset = 1;
	trc->priv->y_offset = 1;


	gcm_trc_widget_draw_bounding_box (cr, 0, 0, trc->priv->chart_width, trc->priv->chart_height);
	if (trc->priv->use_grid)
		gcm_trc_widget_draw_grid (trc, cr);

	gcm_trc_widget_draw_line (trc, cr);

	cairo_restore (cr);
}
