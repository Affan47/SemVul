SetCurrentStyle()
{


  if (this->JoystickOrTrackball == VTKIS_JOYSTICK &&
      this->CameraOrActor == VTKIS_CAMERA)
    {
    if(this->CurrentStyle != this->JoystickCamera)
      {
      if(this->CurrentStyle)
        {
        this->CurrentStyle->SetInteractor(0);
        }
      this->CurrentStyle = this->JoystickCamera;
      }
    }
  else if (this->JoystickOrTrackball == VTKIS_JOYSTICK &&
           this->CameraOrActor == VTKIS_ACTOR)
    {
    if(this->CurrentStyle != this->JoystickActor)
      {
      if(this->CurrentStyle)
        {
        this->CurrentStyle->SetInteractor(0);
        }
      this->CurrentStyle = this->JoystickActor;
      }
    }
  else if (this->JoystickOrTrackball == VTKIS_TRACKBALL &&
           this->CameraOrActor == VTKIS_CAMERA)
    {
    if(this->CurrentStyle != this->TrackballCamera)
      {
      if(this->CurrentStyle)
        {
        this->CurrentStyle->SetInteractor(0);
        }
      this->CurrentStyle = this->TrackballCamera;
      }
    }
  else if (this->JoystickOrTrackball == VTKIS_TRACKBALL &&
           this->CameraOrActor == VTKIS_ACTOR)
    {
      if(this->CurrentStyle != this->TrackballActor)
        {
        if(this->CurrentStyle)
          {
          this->CurrentStyle->SetInteractor(0);
          }
        this->CurrentStyle = this->TrackballActor;
        }
    }
  if (this->CurrentStyle)
    {
    this->CurrentStyle->SetInteractor(this->Interactor);
    this->CurrentStyle->SetTDxStyle(this->TDxStyle);
    }
}
