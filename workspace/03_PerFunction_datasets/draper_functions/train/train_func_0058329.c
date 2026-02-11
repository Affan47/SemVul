LabToXYZ(double L, double a, double b,
                       double *x, double *y, double *z)
{

  double var_Y = ( L + 16 ) / 116;
  double var_X = a / 500 + var_Y;
  double var_Z = var_Y - b / 200;

  if ( pow(var_Y,3) > 0.008856 ) var_Y = pow(var_Y,3);
  else var_Y = ( var_Y - 16.0 / 116.0 ) / 7.787;

  if ( pow(var_X,3) > 0.008856 ) var_X = pow(var_X,3);
  else var_X = ( var_X - 16.0 / 116.0 ) / 7.787;

  if ( pow(var_Z,3) > 0.008856 ) var_Z = pow(var_Z,3);
  else var_Z = ( var_Z - 16.0 / 116.0 ) / 7.787;
  const double ref_X = 0.9505;
  const double ref_Y = 1.000;
  const double ref_Z = 1.089;
  *x = ref_X * var_X;
  *y = ref_Y * var_Y;
  *z = ref_Z * var_Z;
}
