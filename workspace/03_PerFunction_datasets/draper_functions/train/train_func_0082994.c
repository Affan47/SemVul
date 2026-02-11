position_combobox_changed_cb (GtkComboBox *combo_box,
			      gpointer     user_data)
{
	GthImagePrintJob *self = user_data;

	if (self->priv->selected == NULL)
		return;

	if (gtk_combo_box_get_active (combo_box) == 0) {
		self->priv->selected->image_box.x = (self->priv->selected->boundary_box.width - self->priv->selected->image_box.width) / 2.0;
		self->priv->selected->image_box.y = (self->priv->selected->boundary_box.height - self->priv->selected->comment_box.height - self->priv->selected->image_box.height) / 2.0;
		self->priv->selected->transformation.x = self->priv->selected->image_box.x / self->priv->max_image_width;
		self->priv->selected->transformation.y = self->priv->selected->image_box.y / self->priv->max_image_height;
		gth_image_print_job_update_preview (self);
	}
}
