gth_grid_view_cursor_changed (GthFileView *file_view,
			      int          pos)
{
	GthGridView     *self = GTH_GRID_VIEW (file_view);
	GthGridViewItem *old_item;
	GList           *link;
	GthGridViewItem *new_item;

	old_item = NULL;
	if (self->priv->focused_item >= 0) {
		link = g_list_nth (self->priv->items, self->priv->focused_item);
		if (link != NULL)
			old_item = link->data;
	}

	link = g_list_nth (self->priv->items, pos);
	g_return_if_fail (link != NULL);

	self->priv->focused_item = pos;
	if (old_item != NULL) {
		old_item->state ^= GTK_STATE_FLAG_FOCUSED | GTK_STATE_FLAG_ACTIVE;
		_gth_grid_view_queue_draw_item (self, old_item);
	}

	new_item = link->data;
	new_item->state |= GTK_STATE_FLAG_FOCUSED | GTK_STATE_FLAG_ACTIVE;
	_gth_grid_view_queue_draw_item (self, new_item);

	self->priv->make_focused_visible = TRUE;
	_gth_grid_view_make_item_fully_visible (self, self->priv->focused_item);
}
