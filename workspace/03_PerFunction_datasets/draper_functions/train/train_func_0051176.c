get_first_visible_at_offset (GthGridView *self,
			     double       ofs)
{
	int    n_line;
	GList *scan;
	int    pos;

	if ((self->priv->n_items == 0) || (self->priv->lines == NULL))
		return -1;

	n_line = 0;
	for (scan = self->priv->lines; scan && (ofs > 0.0); scan = scan->next) {
		ofs -= GTH_GRID_VIEW_LINE (scan->data)->height + self->priv->cell_spacing;
		n_line++;
	}
	pos = gth_grid_view_get_items_per_line (self) * (n_line - 1);

	return CLAMP (pos, 0, self->priv->n_items - 1);
}
