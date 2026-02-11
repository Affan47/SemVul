ScaleAction(vtkAbstractWidget *w)
{

  vtkBoxWidget2 *self = reinterpret_cast<vtkBoxWidget2*>(w);

  if (self->ScalingEnabled == 0)
  {
    return;
  }


  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  if ( !self->CurrentRenderer ||
       !self->CurrentRenderer->IsInViewport(X,Y) )
    {
    self->WidgetState = vtkBoxWidget2::Start;
    return;
    }


  double e[2];
  e[0] = static_cast<double>(X);
  e[1] = static_cast<double>(Y);
  self->WidgetRep->StartWidgetInteraction(e);
  int interactionState = self->WidgetRep->GetInteractionState();
  if ( interactionState == vtkBoxRepresentation::Outside )
    {
    return;
    }


  self->WidgetState = vtkBoxWidget2::Active;
  self->GrabFocus(self->EventCallbackCommand);
  reinterpret_cast<vtkBoxRepresentation*>(self->WidgetRep)->
    SetInteractionState(vtkBoxRepresentation::Scaling);


  self->EventCallbackCommand->SetAbortFlag(1);
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
  self->Render();
}
