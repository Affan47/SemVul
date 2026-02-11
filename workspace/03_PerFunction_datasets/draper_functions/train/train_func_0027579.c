gth_grid_view_size_allocate (GtkWidget     *widget,
			     GtkAllocation *allocation)
{
	GthGridView *self;
	int          old_cells_per_line;

	self = GTH_GRID_VIEW (widget);

	old_cells_per_line = gth_grid_view_get_items_per_line (self);
	self->priv->width = allocation->width;

	gtk_widget_set_allocation (widget, allocation);

	if (gtk_widget_get_realized (widget)) {
		gdk_window_move_resize (gtk_widget_get_window (widget),
					allocation->x,
					allocation->y,
					allocation->width,
					allocation->height);
		gdk_window_resize (self->priv->bin_window,
				   MAX (self->priv->width, allocation->width),
				   MAX (self->priv->height, allocation->height));

		if (self->priv->needs_relayout || (old_cells_per_line != gth_grid_view_get_items_per_line (self)))
			_gth_grid_view_queue_relayout (self);
	}
	else
		self->priv->needs_relayout_after_size_allocate = TRUE;

	_gth_grid_view_configure_hadjustment (self);
	_gth_grid_view_configure_vadjustment (self);
}
