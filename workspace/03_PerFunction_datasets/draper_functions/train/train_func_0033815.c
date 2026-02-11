GetTransformedFocalPoint(double a[3])
{
  if(this->TransformMatrix)
    {
    double f[4];
    f[0] = this->FocalPoint[0];
    f[1] = this->FocalPoint[1];
    f[2] = this->FocalPoint[2];
    f[3] = 1.0;

    this->TransformMatrix->MultiplyPoint(f, f);

    a[0] = f[0];
    a[1] = f[1];
    a[2] = f[2];
    }
  else
    {
    a[0] = this->FocalPoint[0];
    a[1] = this->FocalPoint[1];
    a[2] = this->FocalPoint[2];
    }
}
