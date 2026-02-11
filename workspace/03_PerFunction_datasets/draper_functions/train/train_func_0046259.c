Cotangent(double point0[3], double point1[3], double point2[3])
  {
  double norm0Squared, norm1Squared, dot, crossNorm, cotangent;

  norm0Squared = (point0[0]-point1[0])*(point0[0]-point1[0]) + (point0[1]-point1[1])*(point0[1]-point1[1]) + (point0[2]-point1[2])*(point0[2]-point1[2]);

  norm1Squared = (point2[0]-point1[0])*(point2[0]-point1[0]) + (point2[1]-point1[1])*(point2[1]-point1[1]) + (point2[2]-point1[2])*(point2[2]-point1[2]);

  dot = (point0[0]-point1[0])*(point2[0]-point1[0]) + (point0[1]-point1[1])*(point2[1]-point1[1]) + (point0[2]-point1[2])*(point2[2]-point1[2]);

  crossNorm = sqrt(norm0Squared * norm1Squared - dot*dot);

  cotangent = 0.0;

  if (crossNorm < GetTolerance(crossNorm))
    {
    if (fabs(dot) < GetTolerance(dot))
      cotangent = 0.0;
    else
      cotangent = GetLarge(cotangent);
    }
  else if (fabs(dot) < GetTolerance(dot))
    {
    cotangent = 0.0;
    }
  else
    {
    cotangent = dot / crossNorm;
    }

  return cotangent;
  }
