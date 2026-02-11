ganv_item_i2w(GanvItem* item, double* x, double* y)
{
	g_return_if_fail(GANV_IS_ITEM(item));
	g_return_if_fail(x != NULL);
	g_return_if_fail(y != NULL);

	cairo_matrix_t matrix;
	ganv_item_i2w_affine(item, &matrix);

	cairo_matrix_transform_point(&matrix, x, y);
}
