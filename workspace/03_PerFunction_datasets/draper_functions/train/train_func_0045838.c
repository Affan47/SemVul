EvaluatePosition(double x[3], double* closestPoint,
                                int& subId, double pcoords[3],
                                double& dist2, double *weights)
{
  double X[3];

  subId = 0;
  pcoords[1] = pcoords[2] = 0.0;

  this->Points->GetPoint(0, X);
  if (closestPoint)
    {
    closestPoint[0] = X[0]; closestPoint[1] = X[1]; closestPoint[2] = X[2];
    }

  dist2 = vtkMath::Distance2BetweenPoints(X,x);
  weights[0] = 1.0;

  if (dist2 == 0.0)
    {
    pcoords[0] = 0.0;
    return 1;
    }
  else
    {
    pcoords[0] = -10.0;
    return 0;
    }
}
