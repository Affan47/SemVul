_gth_slideshow_reset_current (GthSlideshow *self)
{
	if (self->priv->random_order)
		self->priv->file_list = g_list_sort (self->priv->file_list, shuffle_func);

	if (self->priv->direction == GTH_SLIDESHOW_DIRECTION_FORWARD)
		self->priv->current = g_list_first (self->priv->file_list);
	else
		self->priv->current = g_list_last (self->priv->file_list);
}
