gth_grid_view_store_items_state (GthGridView *self)
{
	GList *scan;

	for (scan = self->priv->items; scan; scan = scan->next) {
		GthGridViewItem *item = scan->data;
		item->tmp_state = item->state;
	}
}
