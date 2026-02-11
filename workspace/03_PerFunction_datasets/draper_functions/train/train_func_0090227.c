OnMouseMove()
{
  int x = this->Interactor->GetEventPosition()[0];
  int y = this->Interactor->GetEventPosition()[1];
  this->FindPokedRenderer(x, y);
  vtkCamera* cam = this->CurrentRenderer->GetActiveCamera();
  switch (this->State)
    {
    case VTKIS_FORWARDFLY:
    case VTKIS_REVERSEFLY:
      this->UpdateMouseSteering(cam);
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;
    }
}
