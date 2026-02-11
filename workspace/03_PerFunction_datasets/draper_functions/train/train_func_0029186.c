SetRadius(double r)
{
  r = (r <= this->InitialLength*1.0e-04 ? this->InitialLength*1.0e-04 : r);
  if ( r != this->SphereSource->GetRadius() )
    {
    double center[3];
    this->SphereSource->SetRadius(r);
    this->SphereSource->GetCenter(center);
    this->PlaceHandle(center,r);
    this->SphereSource->Update();
    this->Modified();
    }
}
