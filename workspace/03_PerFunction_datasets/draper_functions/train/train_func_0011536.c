SetPoint1DisplayPosition(double x[3])
{
  if (!this->Point1Representation)
    {
    vtkErrorMacro("SetPoint1DisplayPosition: null point 1 representation");
    return;
    }
  this->Point1Representation->SetDisplayPosition(x);
  double p[3];
  this->Point1Representation->GetWorldPosition(p);
  this->Point1Representation->SetWorldPosition(p);
}
