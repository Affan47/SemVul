_gth_grid_view_relayout_cb (gpointer data)
{
	GthGridView *self = data;

	if (self->priv->layout_timeout != 0) {
		g_source_remove (self->priv->layout_timeout);
		self->priv->layout_timeout = 0;
	}

	_gth_grid_view_relayout_from_line (self, self->priv->relayout_from_line);

	if (self->priv->make_focused_visible) {
		self->priv->make_focused_visible = FALSE;
		_gth_grid_view_make_item_fully_visible (self, self->priv->focused_item);
	}

	if (self->priv->initial_vscroll > 0) {
		gtk_adjustment_set_value (self->priv->vadjustment, self->priv->initial_vscroll);
		self->priv->initial_vscroll = 0;
	}

	return FALSE;
}
