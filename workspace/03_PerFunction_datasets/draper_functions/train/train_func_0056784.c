WidgetInteraction(double e[2])
{

  vtkCamera *camera = this->Renderer->GetActiveCamera();
  if ( !camera )
    {
    return;
    }
  double focalPoint[4], pickPoint[4], prevPickPoint[4];
  double z, vpn[3];


  vtkInteractorObserver::ComputeWorldToDisplay(this->Renderer,
    this->LastPickPosition[0], this->LastPickPosition[1], this->LastPickPosition[2],
    focalPoint);
  z = focalPoint[2];
  vtkInteractorObserver::ComputeDisplayToWorld(this->Renderer,this->LastEventPosition[0],
                                               this->LastEventPosition[1], z, prevPickPoint);
  vtkInteractorObserver::ComputeDisplayToWorld(this->Renderer, e[0], e[1], z, pickPoint);


  if (this->InteractionState == vtkSplineRepresentation::Moving)
    {
    if (this->CurrentHandleIndex != -1)
      {
      this->MovePoint(prevPickPoint, pickPoint);
      }
    else
      {
       this->Translate(prevPickPoint, pickPoint);
      }
    }
  else if (this->InteractionState == vtkSplineRepresentation::Scaling)
    {
    this->Scale(prevPickPoint, pickPoint,
      static_cast<int>(e[0]), static_cast<int>(e[1]));
    }
  else if (this->InteractionState == vtkSplineRepresentation::Spinning)
    {
    camera->GetViewPlaneNormal(vpn);
    this->Spin(prevPickPoint, pickPoint, vpn);
    }

  if (this->ProjectToPlane)
    {
    this->ProjectPointsToPlane();
    }

  this->BuildRepresentation();


  this->LastEventPosition[0] = e[0];
  this->LastEventPosition[1] = e[1];
  this->LastEventPosition[2] = 0.0;
}
