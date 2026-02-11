OnMouseMove()
{

  if ( this->State == vtkPlaneWidget::Outside ||
       this->State == vtkPlaneWidget::Start )
    {
    return;
    }

  int X = this->Interactor->GetEventPosition()[0];
  int Y = this->Interactor->GetEventPosition()[1];


  double focalPoint[4], pickPoint[4], prevPickPoint[4];
  double z, vpn[3];

  vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
  if ( !camera )
    {
    return;
    }


  this->ComputeWorldToDisplay(this->LastPickPosition[0],
                              this->LastPickPosition[1],
                              this->LastPickPosition[2], focalPoint);
  z = focalPoint[2];
  this->ComputeDisplayToWorld(
    double(this->Interactor->GetLastEventPosition()[0]),
    double(this->Interactor->GetLastEventPosition()[1]),
    z, prevPickPoint);
  this->ComputeDisplayToWorld(double(X), double(Y), z, pickPoint);


  if ( this->State == vtkPlaneWidget::Moving )
    {

    if ( this->CurrentHandle )
      {
      if ( this->CurrentHandle == this->Handle[0] )
        {
        this->MoveOrigin(prevPickPoint, pickPoint);
        }
      else if ( this->CurrentHandle == this->Handle[1] )
        {
        this->MovePoint1(prevPickPoint, pickPoint);
        }
      else if ( this->CurrentHandle == this->Handle[2] )
        {
        this->MovePoint2(prevPickPoint, pickPoint);
        }
      else if ( this->CurrentHandle == this->Handle[3] )
        {
        this->MovePoint3(prevPickPoint, pickPoint);
        }
      }
    else
      {
      this->Translate(prevPickPoint, pickPoint);
      }
    }
  else if ( this->State == vtkPlaneWidget::Scaling )
    {
    this->Scale(prevPickPoint, pickPoint, X, Y);
    }
  else if ( this->State == vtkPlaneWidget::Pushing )
    {
    this->Push(prevPickPoint, pickPoint);
    }
  else if ( this->State == vtkPlaneWidget::Rotating )
    {
    camera->GetViewPlaneNormal(vpn);
    this->Rotate(X, Y, prevPickPoint, pickPoint, vpn);
    }
  else if ( this->State == vtkPlaneWidget::Spinning )
    {
    this->Spin(prevPickPoint, pickPoint);
    }


  this->EventCallbackCommand->SetAbortFlag(1);
  this->InvokeEvent(vtkCommand::InteractionEvent,NULL);

  this->Interactor->Render();
}
