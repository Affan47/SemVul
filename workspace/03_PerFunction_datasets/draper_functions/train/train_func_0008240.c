MoveAction(vtkAbstractWidget *w)
{
  vtkHandleWidget *self = reinterpret_cast<vtkHandleWidget*>(w);


  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  if ( self->WidgetState == vtkHandleWidget::Start )
    {
    int state = self->WidgetRep->GetInteractionState();
    self->WidgetRep->ComputeInteractionState(X, Y);
    self->SetCursor(self->WidgetRep->GetInteractionState());

    if ( reinterpret_cast<vtkHandleRepresentation*>(self->WidgetRep)->GetActiveRepresentation() &&
         state != self->WidgetRep->GetInteractionState() )
      {
      self->Render();
      }
    return;
    }


  double eventPosition[2];
  eventPosition[0] = static_cast<double>(X);
  eventPosition[1] = static_cast<double>(Y);
  self->WidgetRep->WidgetInteraction(eventPosition);


  self->EventCallbackCommand->SetAbortFlag(1);
  self->InvokeEvent(vtkCommand::InteractionEvent,NULL);
  self->Render();
}
