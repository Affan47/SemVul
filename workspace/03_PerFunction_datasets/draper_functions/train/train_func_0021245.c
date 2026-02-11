stp_dither_matrix_iterated_init(stp_dither_matrix_impl_t *mat, size_t size,
				size_t expt, const unsigned *array)
{
  int i;
  int x, y;
  mat->base = size;
  mat->exp = expt;
  mat->x_size = 1;
  for (i = 0; i < expt; i++)
    mat->x_size *= mat->base;
  mat->y_size = mat->x_size;
  mat->total_size = mat->x_size * mat->y_size;
  mat->matrix = stp_malloc(sizeof(unsigned) * mat->x_size * mat->y_size);
  for (x = 0; x < mat->x_size; x++)
    for (y = 0; y < mat->y_size; y++)
      {
	mat->matrix[x + y * mat->x_size] =
	  calc_ordered_point(x, y, mat->exp, 1, mat->base, array);
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
