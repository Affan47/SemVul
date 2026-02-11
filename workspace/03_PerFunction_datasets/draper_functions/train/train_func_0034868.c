RenderOverlay(vtkViewport *viewport)
{
  int count=0;
  count += this->LinesActor->RenderOverlay(viewport);
  if ( this->Actor->GetVisibility() )
    {
    count +=  this->Actor->RenderOverlay(viewport);
    }
  if ( this->ActiveActor->GetVisibility() )
    {
    count +=  this->ActiveActor->RenderOverlay(viewport);
    }
  return count;
}
