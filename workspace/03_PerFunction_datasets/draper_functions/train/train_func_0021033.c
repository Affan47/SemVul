initializeThinSearch(double thinThickness,
      double xBasis, double yBasis, SearchPattern *searchPattern)
{


  int ijmax = (int) (thinThickness + 0.5) + 1;
  for (int j = -ijmax; j <= ijmax; j++)
    for (int i = -ijmax; i <= ijmax; i++)
    {
      double x = (double) i;
      double y = (double) j;


      if (x * xBasis + y * yBasis > 0)
      {

        if (distancetoline(x, y, 0.0, 0.0, xBasis, yBasis) <= 0.5)
        {

          SearchPoint *p = new SearchPoint(i, j, sqrt((double) (i * i + j * j)));
          CHECK_PTR_ENGAUGE(p);

          searchPattern->append(p);
        }
      }
    }


  searchPattern->sort();
}
