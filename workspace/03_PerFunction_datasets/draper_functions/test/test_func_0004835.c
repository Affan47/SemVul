SetDisplayPosition(double p[3])
{
  this->Superclass::SetDisplayPosition(p);
  this->FocalPoint->SetPoint(0, p);
  this->FocalPoint->Modified();

  if (this->PointPlacer)
    {

    return;
    }

  double w[4];
  if( this->Renderer )
    {
    vtkInteractorObserver::ComputeDisplayToWorld(
      this->Renderer, p[0], p[1], p[2], w);
    this->SetWorldPosition(w);
    }
}
