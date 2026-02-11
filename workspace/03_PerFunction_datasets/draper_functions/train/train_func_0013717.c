ComputeBoundaryBarycenter(vtkPoints* points, double* barycenter)
{
  int numberOfPoints;
  double weightSum, weight;
  vtkIdType i;


  numberOfPoints = points->GetNumberOfPoints();

  weightSum = 0.0;

  barycenter[0] = 0.0;
  barycenter[1] = 0.0;
  barycenter[2] = 0.0;

  double point0[3], point1[3];

  for (i=0; i<numberOfPoints; i++)
    {
    points->GetPoint(i,point0);
    points->GetPoint((i+1)%numberOfPoints,point1);
    weight = sqrt(vtkMath::Distance2BetweenPoints(point0,point1));
    if (weight < VTK_VMTK_DOUBLE_TOL)
      {
      continue;
      }
    weightSum += weight;

    barycenter[0] += (point0[0] + point1[0])/2.0 * weight;
    barycenter[1] += (point0[1] + point1[1])/2.0 * weight;
    barycenter[2] += (point0[2] + point1[2])/2.0 * weight;
    }

  barycenter[0] /= weightSum;
  barycenter[1] /= weightSum;
  barycenter[2] /= weightSum;
}
