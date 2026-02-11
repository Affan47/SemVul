DistanceToLine(double x[3], double p1[3], double p2[3],
                              double &t, double closestPoint[3])
{
  double p21[3], denom, num;
  double *closest;
  double tolerance;


  p21[0] = p2[0]- p1[0];
  p21[1] = p2[1]- p1[1];
  p21[2] = p2[2]- p1[2];


  num = p21[0]*(x[0]-p1[0]) + p21[1]*(x[1]-p1[1]) + p21[2]*(x[2]-p1[2]);
  denom = vtkMath::Dot(p21,p21);


  tolerance = VTK_TOL*num;
  if (tolerance < 0.0)
    {
    tolerance = -tolerance;
    }
  if ( -tolerance < denom && denom < tolerance )
    {
    closest = p1;
    }


  else if ( denom <= 0.0 || (t=num/denom) < 0.0 )
    {
    closest = p1;
    }
  else if ( t > 1.0 )
    {
    closest = p2;
    }
  else
    {
    closest = p21;
    p21[0] = p1[0] + t*p21[0];
    p21[1] = p1[1] + t*p21[1];
    p21[2] = p1[2] + t*p21[2];
    }

  closestPoint[0] = closest[0];
  closestPoint[1] = closest[1];
  closestPoint[2] = closest[2];
  return vtkMath::Distance2BetweenPoints(closest,x);
}
