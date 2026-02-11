RenderOverlay(vtkViewport *viewport)
{
  int renderedSomething=0;


  if ( ! this->RenderSomething )
    {
    return 0;
    }


  if ( this->XAxisVisibility )
    {
    renderedSomething += this->XAxis->RenderOverlay(viewport);
    }
  if ( this->YAxisVisibility )
    {
    renderedSomething += this->YAxis->RenderOverlay(viewport);
    }
  if ( this->ZAxisVisibility )
    {
    renderedSomething += this->ZAxis->RenderOverlay(viewport);
    }

  return renderedSomething;
}
