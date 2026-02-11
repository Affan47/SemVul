OnMouseMove()
{
  int x = this->Interactor->GetEventPosition()[0];
  int y = this->Interactor->GetEventPosition()[1];

  switch (this->State)
    {
    case VTKIS_ROTATE:
    case VTKIS_PAN:
    case VTKIS_DOLLY:
    case VTKIS_SPIN:
      this->FindPokedRenderer(x, y);
      this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
      break;
    }
}
