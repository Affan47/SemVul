SelectAction(vtkAbstractWidget *w)
{
  vtkLineWidget2 *self = reinterpret_cast<vtkLineWidget2*>(w);
  if ( self->WidgetRep->GetInteractionState() == vtkLineRepresentation::Outside )
    {
    return;
    }


  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  self->WidgetState = vtkLineWidget2::Active;
  self->GrabFocus(self->EventCallbackCommand);
  double e[2];
  e[0] = static_cast<double>(X);
  e[1] = static_cast<double>(Y);
  reinterpret_cast<vtkLineRepresentation*>(self->WidgetRep)->
    StartWidgetInteraction(e);
  self->InvokeEvent(vtkCommand::LeftButtonPressEvent,NULL);
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
  self->EventCallbackCommand->SetAbortFlag(1);
}
