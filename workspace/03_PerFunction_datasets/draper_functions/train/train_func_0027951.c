e_map_draw (GtkWidget *widget,
            cairo_t *cr)
{
	EMap *map;
	cairo_matrix_t matrix;

	if (!gtk_widget_is_drawable (widget))
		return FALSE;

	map = E_MAP (widget);

	cairo_save (cr);

	e_map_tweens_compute_matrix (map, &matrix);
	cairo_transform (cr, &matrix);

	cairo_set_source_surface (cr, map->priv->map_render_surface, 0, 0);
	cairo_paint (cr);

	cairo_restore (cr);

	return FALSE;
}
