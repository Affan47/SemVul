UpdateMouseSteering(vtkCamera *cam)
{
  int *thispos = this->Interactor->GetEventPosition();
  int *lastpos = this->Interactor->GetLastEventPosition();

  double aspeed = this->AngleStepSize*(this->Interactor->GetShiftKey() ?
      this->AngleAccelerationFactor : 1.0);


  int *size = this->Interactor->GetSize();
  double scalefactor = 5*cam->GetViewAngle()/size[0];
  double dx = - (thispos[0] - lastpos[0])*scalefactor*aspeed;
  double dy =   (thispos[1] - lastpos[1])*scalefactor*aspeed;


  this->DeltaPitch = dy;
  this->DeltaYaw = dx;


}
