gdip_is_scaled (GpGraphics *graphics)
{
	cairo_matrix_t matrix;
	cairo_get_matrix (graphics->ct, &matrix);
	return ((matrix.xx != 1.0f) || (matrix.yy != 1.0f));
}
