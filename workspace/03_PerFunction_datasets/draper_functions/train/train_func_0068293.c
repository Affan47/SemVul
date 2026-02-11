GetBounds ()
{
  double x[3];
  int i, numPts=this->Points->GetNumberOfPoints();

  if (numPts)
    {
    this->Points->GetPoint(0, x);
    this->Bounds[0] = x[0];
    this->Bounds[2] = x[1];
    this->Bounds[4] = x[2];
    this->Bounds[1] = x[0];
    this->Bounds[3] = x[1];
    this->Bounds[5] = x[2];
    for (i=1; i<numPts; i++)
      {
      this->Points->GetPoint(i, x);
      this->Bounds[0] = (x[0] < this->Bounds[0] ? x[0] : this->Bounds[0]);
      this->Bounds[1] = (x[0] > this->Bounds[1] ? x[0] : this->Bounds[1]);
      this->Bounds[2] = (x[1] < this->Bounds[2] ? x[1] : this->Bounds[2]);
      this->Bounds[3] = (x[1] > this->Bounds[3] ? x[1] : this->Bounds[3]);
      this->Bounds[4] = (x[2] < this->Bounds[4] ? x[2] : this->Bounds[4]);
      this->Bounds[5] = (x[2] > this->Bounds[5] ? x[2] : this->Bounds[5]);
      }
    }
  else
    {
    vtkMath::UninitializeBounds(this->Bounds);
    }
  return this->Bounds;
}
