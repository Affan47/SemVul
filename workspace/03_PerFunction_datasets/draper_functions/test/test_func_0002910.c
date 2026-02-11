IntersectWithLine(double p1[3], double p2[3], double tol, double& t,
                               double x[3], double pcoords[3], int& subId)
{
  double a1[3], a2[3];
  double projXYZ[3];
  int i;

  subId = 0;
  pcoords[1] = pcoords[2] = 0.0;

  this->Points->GetPoint(0, a1);
  this->Points->GetPoint(1, a2);

  if ( this->Intersection(p1, p2, a1, a2, t, pcoords[0]) ==
       VTK_YES_INTERSECTION )
    {

    for (i=0; i<3; i++)
      {
      x[i] = a1[i] + pcoords[0]*(a2[i]-a1[i]);
      projXYZ[i] = p1[i] + t*(p2[i]-p1[i]);
      }
    if ( vtkMath::Distance2BetweenPoints(x,projXYZ) <= tol*tol )
      {
      return 1;
      }
    else
      {
      return 0;
      }
    }

  else
    {

    if (t < 0.0)
      {
      t = 0.0;
      if (vtkLine::DistanceToLine(p1,a1,a2,pcoords[0],x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    if (t > 1.0)
      {
      t = 1.0;
      if (vtkLine::DistanceToLine(p2,a1,a2,pcoords[0],x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    if (pcoords[0] < 0.0)
      {
      pcoords[0] = 0.0;
      if (vtkLine::DistanceToLine(a1,p1,p2,t,x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    if (pcoords[0] > 1.0)
      {
      pcoords[0] = 1.0;
      if (vtkLine::DistanceToLine(a2,p1,p2,t,x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    }
  return 0;
}
