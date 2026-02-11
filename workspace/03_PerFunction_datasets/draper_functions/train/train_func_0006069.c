_gth_grid_view_free_lines_from (GthGridView *self,
				int          first_line)
{
	GList *lines;
	GList *scan;

	lines = g_list_nth (self->priv->lines, first_line);
	if (lines == NULL)
		return;


	if (lines->prev != NULL)
		lines->prev->next = NULL;
	else
		self->priv->lines = NULL;

	for (scan = lines; scan; scan = scan->next)
		gth_grid_view_line_free (GTH_GRID_VIEW_LINE (scan->data));
	g_list_free (lines);
}
