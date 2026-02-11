StartWidgetInteraction(double e[2])
{

  this->StartEventPosition[0] = e[0];
  this->StartEventPosition[1] = e[1];
  this->StartEventPosition[2] = 0.0;


  this->LastEventPosition[0] = e[0];
  this->LastEventPosition[1] = e[1];
  this->LastEventPosition[2] = 0.0;


  this->Point1Representation->GetWorldPosition(this->StartP1);
  this->Point2Representation->GetWorldPosition(this->StartP2);
  this->LineHandleRepresentation->GetWorldPosition(this->StartLineHandle);

  if ( this->InteractionState == vtkLineRepresentation::Scaling )
    {
    double dp1[3], dp2[3];
    this->Point1Representation->GetDisplayPosition(dp1);
    this->Point2Representation->GetDisplayPosition(dp2);
    this->Length = sqrt((dp1[0]-dp2[0])*(dp1[0]-dp2[0]) + (dp1[1]-dp2[1])*(dp1[1]-dp2[1]));
    }
}
