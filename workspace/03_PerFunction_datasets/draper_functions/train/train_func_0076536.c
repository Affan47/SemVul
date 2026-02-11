SetNormal(double x, double y, double z)
{
  double n[3], n2[3];
  n[0] = x;
  n[1] = y;
  n[2] = z;
  vtkMath::Normalize(n);

  this->Plane->GetNormal(n2);
  if ( n[0] != n2[0] || n[1] != n2[1] || n[2] != n2[2] )
    {
    this->Plane->SetNormal(n);
    this->Modified();
    }
}
