R3Centroid(int npoints, R3Point *points)
{

  R3Point centroid(0.0, 0.0, 0.0);
  for (int i = 0; i < npoints; i++)
    centroid += points[i];
  centroid /= npoints;


  return centroid;
}
