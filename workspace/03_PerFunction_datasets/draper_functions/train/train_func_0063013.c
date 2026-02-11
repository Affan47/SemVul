Scale(double *p1, double *p2,
                                    int vtkNotUsed(X), int Y)
{

  double v[3];
  v[0] = p2[0] - p1[0];
  v[1] = p2[1] - p1[1];
  v[2] = p2[2] - p1[2];

  double radius = this->SphereSource->GetRadius();
  double *c = this->SphereSource->GetCenter();


  double sf = vtkMath::Norm(v) / radius;
  if ( Y > this->LastEventPosition[1] )
    {
    sf = 1.0 + sf;
    }
  else
    {
    sf = 1.0 - sf;
    }


  if ( Y <= this->LastEventPosition[1] && sf*radius < 1.0e-06*this->InitialLength )
    {
    return;
    }


  this->SphereSource->SetRadius(sf*radius);
  this->HandlePosition[0] = c[0]+sf*(this->HandlePosition[0]-c[0]);
  this->HandlePosition[1] = c[1]+sf*(this->HandlePosition[1]-c[1]);
  this->HandlePosition[2] = c[2]+sf*(this->HandlePosition[2]-c[2]);
  this->HandleSource->SetCenter(this->HandlePosition);
}
