placement_grid_new (NemoIconContainer *container, gboolean tight)
{
	PlacementGrid *grid;
	int width, height;
	int num_columns;
	int num_rows;
	int i;
	GtkAllocation allocation;


	gtk_widget_get_allocation (GTK_WIDGET (container), &allocation);
	width  = CANVAS_WIDTH(container, allocation);
	height = CANVAS_HEIGHT(container, allocation);

	num_columns = width / SNAP_SIZE_X;
	num_rows = height / SNAP_SIZE_Y;

	if (num_columns == 0 || num_rows == 0) {
		return NULL;
	}

	grid = g_new0 (PlacementGrid, 1);
	grid->tight = tight;
	grid->num_columns = num_columns;
	grid->num_rows = num_rows;

	grid->grid_memory = g_new0 (int, (num_rows * num_columns));
	grid->icon_grid = g_new0 (int *, num_columns);

	for (i = 0; i < num_columns; i++) {
		grid->icon_grid[i] = grid->grid_memory + (i * num_rows);
	}

	return grid;
}
