gt_double_relative_equal(double d1, double d2)
{
  double relerr;
  if (fabs(d1 - d2) < GT_DBL_MAX_ABS_ERROR)
    return true;
  if (fabs(d2) > fabs(d1))
    relerr = fabs((d1 - d2) / d2);
  else
    relerr = fabs((d1 - d2) / d1);
  if (relerr <= GT_DBL_MAX_REL_ERROR)
    return true;
  return false;
}
