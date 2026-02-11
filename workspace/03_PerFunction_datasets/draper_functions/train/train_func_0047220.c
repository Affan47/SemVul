WidgetInteraction(double e[2])
{


  double focalPoint[4], pickPoint[4], prevPickPoint[4];
  double z, vpn[3];

  vtkCamera *camera = this->Renderer->GetActiveCamera();
  if ( !camera )
    {
    return;
    }


  double pos[3];
  this->Picker->GetPickPosition(pos);
  vtkInteractorObserver::ComputeWorldToDisplay(this->Renderer, pos[0], pos[1], pos[2],
                                               focalPoint);
  z = focalPoint[2];
  vtkInteractorObserver::ComputeDisplayToWorld(this->Renderer,this->LastEventPosition[0],
                                               this->LastEventPosition[1], z, prevPickPoint);
  vtkInteractorObserver::ComputeDisplayToWorld(this->Renderer, e[0], e[1], z, pickPoint);


  if ( this->InteractionState == vtkImplicitPlaneRepresentation::MovingOutline )
    {
    this->TranslateOutline(prevPickPoint, pickPoint);
    }
  else if ( this->InteractionState == vtkImplicitPlaneRepresentation::MovingOrigin )
    {
    this->TranslateOrigin(prevPickPoint, pickPoint);
    }
  else if ( this->InteractionState == vtkImplicitPlaneRepresentation::Pushing )
    {
    this->Push(prevPickPoint, pickPoint);
    }
  else if ( this->InteractionState == vtkImplicitPlaneRepresentation::Scaling &&
    this->ScaleEnabled )
    {
    this->Scale(prevPickPoint, pickPoint, e[0], e[1]);
    }
  else if ( this->InteractionState == vtkImplicitPlaneRepresentation::Rotating )
    {
    camera->GetViewPlaneNormal(vpn);
    this->Rotate(e[0], e[1], prevPickPoint, pickPoint, vpn);
    }
  else if( this->InteractionState == vtkImplicitPlaneRepresentation::Outside &&
    this->LockNormalToCamera )
    {
    this->SetNormalToCamera();
    }

  this->LastEventPosition[0] = e[0];
  this->LastEventPosition[1] = e[1];
  this->LastEventPosition[2] = 0.0;
}
