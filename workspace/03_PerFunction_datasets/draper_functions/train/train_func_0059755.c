OnMouseWheelForward()
{
  this->FindPokedRenderer(
    this->Interactor->GetEventPosition()[0],
    this->Interactor->GetEventPosition()[1]);
  vtkCamera* camera = this->CurrentRenderer->GetActiveCamera();
  if (!camera)
    {
    return;
    }
  this->Interaction = ZOOMING;
  double motion = 10.0;
  double dyf = motion * 0.2;
  double factor = pow(1.1, dyf);
  camera->SetParallelScale(camera->GetParallelScale() / factor);
  this->InvokeEvent(vtkCommand::InteractionEvent);
  this->GetInteractor()->Render();
  this->Interaction = NONE;
}
