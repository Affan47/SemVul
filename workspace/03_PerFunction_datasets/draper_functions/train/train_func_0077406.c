_gth_grid_view_unselect_all (GthGridView *self,
			     gpointer     keep_selected)
{
	GthGridViewPrivate *priv = self->priv;
	int                 idx;
	GList              *scan;
	int                 i;

	idx = 0;
	for (scan = priv->items, i = 0;
	     scan != NULL;
	     scan = scan->next, i++)
	{
		GthGridViewItem *item = scan->data;

		if (item == keep_selected)
			idx = i;
		else if (item->state & GTK_STATE_FLAG_SELECTED)
			_gth_grid_view_set_item_selected (self, FALSE, i);
	}

	return idx;
}
