singlePointSetScreenLimits(PointSet* p, bool* first,
  double* xMin, double* xMax, double* yMin, double* yMax)
{
  double xmin, xmax, ymin, ymax;

  ASSERT_ENGAUGE(p != 0);
  if (p->pointSetScreenLimits(&xmin, &xmax, &ymin, &ymax))
  {
    if (*first || (xmin < *xMin))
      *xMin = xmin;
    if (*first || (xmax > *xMax))
      *xMax = xmax;
    if (*first || (ymin < *yMin))
      *yMin = ymin;
    if (*first || (ymax > *yMax))
      *yMax = ymax;

    *first = false;
  }
}
