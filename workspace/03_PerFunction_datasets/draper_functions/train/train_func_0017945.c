CentroidSize(vtkPoints* pd, double *cp)
{
  Centroid(pd, cp);

  double S = 0;
  for (int i = 0; i < pd->GetNumberOfPoints(); i++)
    {
    double p[3];
    pd->GetPoint(i, p);
    S += vtkMath::Distance2BetweenPoints(p,cp);
  }

  return sqrt(S);
}
