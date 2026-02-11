ScaleAction(vtkAbstractWidget *w)
{

  vtkSphereWidget2 *self = reinterpret_cast<vtkSphereWidget2*>(w);


  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  if ( !self->CurrentRenderer ||
       !self->CurrentRenderer->IsInViewport(X,Y) )
    {
    self->WidgetState = vtkSphereWidget2::Start;
    return;
    }


  double e[2];
  e[0] = static_cast<double>(X);
  e[1] = static_cast<double>(Y);
  self->WidgetRep->StartWidgetInteraction(e);
  int interactionState = self->WidgetRep->GetInteractionState();
  if ( interactionState == vtkSphereRepresentation::Outside )
    {
    return;
    }


  self->WidgetState = vtkSphereWidget2::Active;
  self->GrabFocus(self->EventCallbackCommand);
  reinterpret_cast<vtkSphereRepresentation*>(self->WidgetRep)->
    SetInteractionState(vtkSphereRepresentation::Scaling);


  self->EventCallbackCommand->SetAbortFlag(1);
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
  self->Render();
}
