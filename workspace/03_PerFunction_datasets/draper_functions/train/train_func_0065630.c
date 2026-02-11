RenderOverlay(vtkViewport *viewport)
{
  this->BuildRepresentation();
  int count = this->TubeActor->RenderOverlay(viewport);
  count += this->SliderActor->RenderOverlay(viewport);
  if (this->HighlightState && strlen(this->LabelActor->GetInput()))
    {
    count += this->LabelActor->RenderOverlay(viewport);
    }
  return count;
}
