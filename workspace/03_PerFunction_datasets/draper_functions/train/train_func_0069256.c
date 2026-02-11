ComputeNormal(vtkPoints *p, int numPts, vtkIdType *pts,
                               double *n)
{
  int i;
  double v0[3], v1[3], v2[3];
  double ax, ay, az, bx, by, bz;


  n[0] = n[1] = n[2] = 0.0;
  if ( numPts == 2 || numPts == 1 )
    {
    return;
    }

  if ( numPts == 3 )
    {
    p->GetPoint(pts[0],v0);
    p->GetPoint(pts[1],v1);
    p->GetPoint(pts[2],v2);
    vtkTriangle::ComputeNormal(v0, v1, v2, n);
    return;
    }


  p->GetPoint(pts[0],v1);
  p->GetPoint(pts[1],v2);

  for (i=0; i < numPts; i++)
    {
    v0[0] = v1[0]; v0[1] = v1[1]; v0[2] = v1[2];
    v1[0] = v2[0]; v1[1] = v2[1]; v1[2] = v2[2];
    p->GetPoint(pts[(i+2)%numPts],v2);


    ax = v2[0] - v1[0]; ay = v2[1] - v1[1]; az = v2[2] - v1[2];
    bx = v0[0] - v1[0]; by = v0[1] - v1[1]; bz = v0[2] - v1[2];

    n[0] += (ay * bz - az * by);
    n[1] += (az * bx - ax * bz);
    n[2] += (ax * by - ay * bx);
    }

  vtkMath::Normalize(n);
}
