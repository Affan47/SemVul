ReleaseGraphicsResources(vtkWindow *win)
{
  this->TitleActor->ReleaseGraphicsResources(win);
  if (this->TextMappers != NULL )
    {
    for (int i=0; i < this->NumberOfLabelsBuilt; i++)
      {
      this->TextActors[i]->ReleaseGraphicsResources(win);
      }
    }
  this->ScalarBarActor->ReleaseGraphicsResources(win);
  this->BackgroundActor->ReleaseGraphicsResources(win);
  this->FrameActor->ReleaseGraphicsResources(win);
}
