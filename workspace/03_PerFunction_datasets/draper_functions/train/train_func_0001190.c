RenderTranslucentPolygonalGeometry(vtkViewport *viewport)
{

  int renderedSomething=0;

  this->BuildAxis(viewport, false);


  if (!this->AxisHasZeroLength)
    {
    if(this->DrawGridpolys)
      {
      renderedSomething += this->GridpolysActor->RenderTranslucentPolygonalGeometry(viewport);
      }
    }

  return renderedSomething;
}
