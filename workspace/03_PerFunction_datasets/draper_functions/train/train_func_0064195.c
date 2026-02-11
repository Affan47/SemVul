width_adjustment_value_changed_cb (GtkAdjustment *adjustment,
				   gpointer       user_data)
{
	GthImagePrintJob *self = user_data;

	if (self->priv->selected == NULL)
		return;

	gth_image_print_job_set_selected_zoom (self, TO_PIXELS (gtk_adjustment_get_value (adjustment)) / self->priv->selected->maximized_box.width);
}
