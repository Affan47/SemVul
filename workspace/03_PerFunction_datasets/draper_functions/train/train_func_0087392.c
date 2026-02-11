SetBounds(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
  if ((this->Bounds[0] != xmin) ||
      (this->Bounds[1] != xmax) ||
      (this->Bounds[2] != ymin) ||
      (this->Bounds[3] != ymax) ||
      (this->Bounds[4] != zmin) ||
      (this->Bounds[5] != zmax) )
    {
    this->Bounds[0] = xmin;
    this->Bounds[1] = xmax;
    this->Bounds[2] = ymin;
    this->Bounds[3] = ymax;
    this->Bounds[4] = zmin;
    this->Bounds[5] = zmax;

    this->BoundsTime.Modified();
    }
}
