o_transform  (OMatrix *matrix, int replace)
{
  OMatrix *m = &context()->transform;
  if (replace)
    context()->transform = *matrix;
  else
    o_matrix_multiply (m, matrix, m);
}
