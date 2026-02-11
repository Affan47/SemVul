_gth_grid_view_keep_focus_consistent (GthGridView *self)
{
	if (self->priv->focused_item > self->priv->n_items - 1)
		self->priv->focused_item = - 1;
}
