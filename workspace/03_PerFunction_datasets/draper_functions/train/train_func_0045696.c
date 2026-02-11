StartWidgetInteraction(double startEventPos[2])
{
  this->StartEventPosition[0] = startEventPos[0];
  this->StartEventPosition[1] = startEventPos[1];

  if (this->ManipulationMode == WindowLevelling)
    {
    this->InitialWindow = this->CurrentWindow;
    this->InitialLevel  = this->CurrentLevel;
    }
  else
    {
    if ( vtkResliceCursor *rc = this->GetResliceCursor() )
      {
      rc->GetCenter(this->StartCenterPosition);
      }
    }

  this->LastEventPosition[0] = startEventPos[0];
  this->LastEventPosition[1] = startEventPos[1];
}
