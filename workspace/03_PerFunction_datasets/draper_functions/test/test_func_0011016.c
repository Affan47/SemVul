_gth_grid_view_line_new (GthGridView *self,
		     	 GList       *items,
		     	 int          y,
		     	 int          height)
{
	GthGridViewLine *line;

	line = g_new0 (GthGridViewLine, 1);
	line->items = g_list_reverse (items);
	line->y = y;
	line->height = height;
	_gth_grid_view_layout_line (self, line);

	return line;
}
