gegl_matrix3_is_affine (GeglMatrix3 *matrix)
{
  return is_zero (matrix->coeff[2][0]) &&
         is_zero (matrix->coeff[2][1]) &&
         is_one  (matrix->coeff[2][2]);
}
