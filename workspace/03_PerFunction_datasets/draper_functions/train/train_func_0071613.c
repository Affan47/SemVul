GdipMultiplyMatrix (GpMatrix *matrix, GpMatrix *matrix2, GpMatrixOrder order)
{
	if (!matrix || !matrix2)
		return InvalidParameter;

        if (order == MatrixOrderAppend)
                cairo_matrix_multiply (matrix, matrix, matrix2);
        else if (order == MatrixOrderPrepend)
                cairo_matrix_multiply (matrix, matrix2, matrix);
        else
                return InvalidParameter;

	return Ok;
}
