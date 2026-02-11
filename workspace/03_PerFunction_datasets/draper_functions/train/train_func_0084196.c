GdipGetWorldTransform (GpGraphics *graphics, GpMatrix *matrix)
{
	if (!graphics || !matrix)
		return InvalidParameter;


	gdip_cairo_matrix_copy (matrix, graphics->copy_of_ctm);


	if (!gdip_is_matrix_empty (&graphics->previous_matrix)) {
		cairo_matrix_t inverted;

		gdip_cairo_matrix_copy (&inverted, &graphics->previous_matrix);
		cairo_matrix_invert (&inverted);
		return GdipMultiplyMatrix (matrix, &inverted, MatrixOrderAppend);
	}
        return Ok;
}
