gnome_canvas_item_transform (GnomeCanvasItem *item,
                             const cairo_matrix_t *matrix)
{
	cairo_matrix_t i2p;

	g_return_if_fail (GNOME_IS_CANVAS_ITEM (item));
	g_return_if_fail (matrix != NULL);


	cairo_matrix_multiply (&i2p, matrix, &item->matrix);

	gnome_canvas_item_set_matrix (item, &i2p);
}
