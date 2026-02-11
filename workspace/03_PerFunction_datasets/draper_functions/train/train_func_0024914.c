SetDivisionSpacing(double x, double y, double z)
{
  if (this->ComputeNumberOfDivisions && this->DivisionSpacing[0] == x &&
      this->DivisionSpacing[1] == y && this->DivisionSpacing[2] == z)
    {
    return;
    }
  if ( x <= 0 )
    {
    vtkErrorMacro( << "Spacing (x) should be larger than 0.0, setting to 1.0" );
    x = 1.0;
    }
  if ( y <= 0 )
    {
    vtkErrorMacro( << "Spacing (y) should be larger than 0.0, setting to 1.0" );
    y = 1.0;
    }
  if ( z <= 0 )
    {
    vtkErrorMacro( << "Spacing (z) should be larger than 0.0, setting to 1.0" );
    z = 1.0;
    }
  this->Modified();
  this->DivisionSpacing[0] = x;
  this->DivisionSpacing[1] = y;
  this->DivisionSpacing[2] = z;
  this->ComputeNumberOfDivisions = 1;
}
