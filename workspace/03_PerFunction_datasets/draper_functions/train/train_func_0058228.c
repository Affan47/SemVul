gcr_grid_size_allocate (GtkWidget *w, GtkAllocation *alloc)
{
	GcrGrid *grid = GCR_GRID (w);
	gtk_layout_move (GTK_LAYOUT (grid), grid->scroll, alloc->width - grid->scroll_width, grid->row_height + 1);
	g_object_set (G_OBJECT (grid->scroll), "height-request", alloc->height - grid->row_height - 1, NULL);
	grid->nb_visible = alloc->height / grid->row_height - 1;
	if (grid->rows) {
		gtk_adjustment_set_page_size (grid->vadj, static_cast < double > (grid->nb_visible) / grid->rows);
		gtk_adjustment_set_upper (grid->vadj, (grid->nb_visible < grid->rows)? grid->rows - grid->nb_visible: .1);
		if (grid->rows < grid->nb_visible + grid->first_visible) {
			grid->first_visible = (grid->nb_visible < grid->rows)? grid->rows - grid->nb_visible: 0;
			gtk_adjustment_set_value (grid->vadj, grid->first_visible);
		}
	} else
		gtk_adjustment_set_page_size (grid->vadj, 1.);

	grid->actual_width = alloc->width - grid->header_width - grid->scroll_width;
	double ratio = static_cast < double > (grid->actual_width) / grid->cols_min_width;
	if (ratio < 0.)
		ratio = 1.;
	double last_pos = 0., pos = 0.;
	for (unsigned i = 0; i < grid->cols; i++) {
		pos += grid->min_widths[i];
		grid->col_widths[i] = pos * ratio - last_pos;
		last_pos += grid->col_widths[i];
	}
	parent_class->size_allocate (w, alloc);
}
