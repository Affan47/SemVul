_cogl_matrix_multiply (CoglMatrix *result,
                       const CoglMatrix *a,
                       const CoglMatrix *b)
{
  result->flags = (a->flags |
                   b->flags |
                   MAT_DIRTY_TYPE |
                   MAT_DIRTY_INVERSE);

  if (TEST_MAT_FLAGS(result, MAT_FLAGS_3D))
    matrix_multiply3x4 ((float *)result, (float *)a, (float *)b);
  else
    matrix_multiply4x4 ((float *)result, (float *)a, (float *)b);
}
