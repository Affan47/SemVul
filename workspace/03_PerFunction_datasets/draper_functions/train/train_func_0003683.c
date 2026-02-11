gcr_grid_unrealize (GtkWidget *w)
{
	GcrGrid *grid = GCR_GRID (w);
	if (grid->cursor_signal > 0)
		g_source_remove (grid->cursor_signal);
	parent_class->unrealize (w);
}
