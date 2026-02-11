gnome_canvas_c2w_matrix (GnomeCanvas *canvas,
                         cairo_matrix_t *matrix)
{
	g_return_if_fail (GNOME_IS_CANVAS (canvas));
	g_return_if_fail (matrix != NULL);

	cairo_matrix_init_translate (
		matrix, canvas->scroll_x1, canvas->scroll_y1);
}
