OnMouseWheelBackward()
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
  this->Superclass::OnMouseWheelBackward();
  this->Interaction = NONE;
}
