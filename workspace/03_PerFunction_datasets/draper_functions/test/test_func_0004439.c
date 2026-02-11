vector_transform_in_place (pv x, const Matrix M)
{
  int i, j;


  pv q = { 0, 0, 0, 0 };


  for (j = 0; j < MATRIX_DIM; ++j)
    {

      for (i = 0; i < MATRIX_DIM; ++i)
	q[i] += M[i + MATRIX_DIM * j] * x[j];
    }


  for (i = 0; i < MATRIX_DIM; i++)
    x[i] = q[i];
}
