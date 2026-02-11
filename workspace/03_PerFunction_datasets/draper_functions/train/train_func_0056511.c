gth_grid_view_select (GthFileSelection *selection,
		      int               pos)
{
	GthGridView *self = GTH_GRID_VIEW (selection);
	GList       *list;
	int          i;

	switch (self->priv->selection_mode) {
	case GTK_SELECTION_SINGLE:
		for (list = self->priv->items, i = 0;
		     list != NULL;
		     list = list->next, i++)
		{
			GthGridViewItem *item = list->data;

			if ((i != pos) && (item->state & GTK_STATE_FLAG_SELECTED))
				_gth_grid_view_set_item_selected (self, FALSE, i);
		}
		_gth_grid_view_set_item_selected (self, TRUE, pos);
		_gth_grid_view_emit_selection_changed (self);
		break;

	case GTK_SELECTION_MULTIPLE:
		self->priv->select_pending = FALSE;

		_gth_grid_view_set_item_selected_and_emit_signal (self, TRUE, pos);
		self->priv->last_selected_pos = pos;
		self->priv->last_selected_item = g_list_nth (self->priv->items, pos)->data;
		break;

	default:
		break;
	}
}
