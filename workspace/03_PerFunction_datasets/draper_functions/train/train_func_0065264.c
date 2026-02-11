SampleTriangle(vtkPoints *newPts, vtkPoints *inPts,
                                             vtkIdType *pts)
{
  double x0[3], x1[3], x2[3];
  inPts->GetPoint(pts[0],x0);
  inPts->GetPoint(pts[1],x1);
  inPts->GetPoint(pts[2],x2);

  double l1 = vtkMath::Distance2BetweenPoints(x0,x1);
  double l2 = vtkMath::Distance2BetweenPoints(x0,x2);
  if ( l1 > this->Distance2 || l2 > this->Distance2 )
    {
    double s, t, x[3];
    l1 = sqrt(l1);
    l2 = sqrt(l2);
    int n1 = static_cast<int>(l1/this->Distance) + 2;
    int n2 = static_cast<int>(l2/this->Distance) + 2;
    n1 = ( n1 < 3 ? 3 : n1);
    n2 = ( n2 < 3 ? 3 : n2);
    for (vtkIdType j=1; j<(n2-1); j++)
      {
      t = static_cast<double>(j)/(n2-1);
      for (vtkIdType i=1; i<(n1-1); i++)
        {
        s = static_cast<double>(i)/(n1-1);
        if ( (1.0 - s - t) > 0.0 )
          {
          x[0] = x0[0] + s*(x1[0]-x0[0]) + t*(x2[0]-x0[0]);
          x[1] = x0[1] + s*(x1[1]-x0[1]) + t*(x2[1]-x0[1]);
          x[2] = x0[2] + s*(x1[2]-x0[2]) + t*(x2[2]-x0[2]);
          newPts->InsertNextPoint(x);
          }
        }
      }
    }
}
