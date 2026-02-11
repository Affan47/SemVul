Scale(double *p1, double *p2,
                                int vtkNotUsed(X), int Y)
{


  double v[3];
  v[0] = p2[0] - p1[0];
  v[1] = p2[1] - p1[1];
  v[2] = p2[2] - p1[2];

  double *o = this->PlaneSource->GetOrigin();
  double *pt1 = this->PlaneSource->GetPoint1();
  double *pt2 = this->PlaneSource->GetPoint2();
  double* center = this->PlaneSource->GetCenter();


  double sf = vtkMath::Norm(v) /
    sqrt(vtkMath::Distance2BetweenPoints(pt1,pt2));
  if ( Y > this->Interactor->GetLastEventPosition()[1] )
    {
    sf = 1.0 + sf;
    }
  else
    {
    sf = 1.0 - sf;
    }


  double origin[3], point1[3], point2[3];

  for (int i=0; i<3; i++)
    {
    origin[i] = sf * (o[i] - center[i]) + center[i];
    point1[i] = sf * (pt1[i] - center[i]) + center[i];
    point2[i] = sf * (pt2[i] - center[i]) + center[i];
    }

  this->PlaneSource->SetOrigin(origin);
  this->PlaneSource->SetPoint1(point1);
  this->PlaneSource->SetPoint2(point2);
}
