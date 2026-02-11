eel_canvas_set_center_scroll_region (EelCanvas *canvas,
				     gboolean center_scroll_region)
{
	GtkAdjustment *vadjustment, *hadjustment;

	g_return_if_fail (EEL_IS_CANVAS (canvas));

	canvas->center_scroll_region = center_scroll_region != 0;

	hadjustment = gtk_scrollable_get_hadjustment (GTK_SCROLLABLE (&canvas->layout));
	vadjustment = gtk_scrollable_get_vadjustment (GTK_SCROLLABLE (&canvas->layout));

	scroll_to (canvas,
		   gtk_adjustment_get_value (hadjustment),
		   gtk_adjustment_get_value (vadjustment));
}
