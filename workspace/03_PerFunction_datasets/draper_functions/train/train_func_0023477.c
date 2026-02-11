ReleaseGraphicsResources(vtkWindow *win)
{
  this->TitleActor->ReleaseGraphicsResources(win);
  this->XAxis->ReleaseGraphicsResources(win);
  this->YAxis->ReleaseGraphicsResources(win);
  for (int i=0; i < this->NumberOfInputs; i++)
    {
    this->PlotActor[i]->ReleaseGraphicsResources(win);
    }
  this->LegendActor->ReleaseGraphicsResources(win);
  if (this->ChartBoxActor)
   {
   this->ChartBoxActor->ReleaseGraphicsResources(win);
   }
  if (this->ChartBorderActor)
   {
   this->ChartBorderActor->ReleaseGraphicsResources(win);
   }
  if (this->ReferenceLinesActor)
   {
   this->ReferenceLinesActor->ReleaseGraphicsResources(win);
   }
}
