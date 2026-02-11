stp_dither_matrix_init(stp_dither_matrix_impl_t *mat, int x_size, int y_size,
		       const unsigned int *array, int transpose, int prescaled)
{
  int x, y;
  mat->base = x_size;
  mat->exp = 1;
  mat->x_size = x_size;
  mat->y_size = y_size;
  mat->total_size = mat->x_size * mat->y_size;
  mat->matrix = stp_malloc(sizeof(unsigned) * mat->x_size * mat->y_size);
  for (x = 0; x < mat->x_size; x++)
    for (y = 0; y < mat->y_size; y++)
      {
	if (transpose)
	  mat->matrix[x + y * mat->x_size] = array[y + x * mat->y_size];
	else
	  mat->matrix[x + y * mat->x_size] = array[x + y * mat->x_size];
	if (!prescaled)
	  mat->matrix[x + y * mat->x_size] =
	    (double) mat->matrix[x + y * mat->x_size] * 65536.0 /
	    (double) (mat->x_size * mat->y_size);
      }
  mat->last_x = mat->last_x_mod = 0;
  mat->last_y = mat->last_y_mod = 0;
  mat->index = 0;
  mat->i_own = 1;
  if (is_po2(mat->x_size))
    mat->fast_mask = mat->x_size - 1;
  else
    mat->fast_mask = 0;
}
