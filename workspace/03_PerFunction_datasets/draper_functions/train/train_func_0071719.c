gth_grid_view_get_at_position (GthFileView *file_view,
			       int          x,
			       int          y)
{
	GthGridView *self = GTH_GRID_VIEW (file_view);
	GList       *scan;
	int          n;

	for (scan = self->priv->items, n = 0;
	     scan != NULL;
	     scan = scan->next, n++)
	{
		GthGridViewItem *item = scan->data;

		if (_cairo_rectangle_contains_point (&item->thumbnail_area, x, y)
		    || _cairo_rectangle_contains_point (&item->caption_area, x, y))
		{
			return n;
		}
	}

	return -1;
}
