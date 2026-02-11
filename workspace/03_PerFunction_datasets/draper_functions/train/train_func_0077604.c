RotateAction(vtkAbstractWidget *w)
{
  vtkResliceCursorWidget *self = reinterpret_cast<vtkResliceCursorWidget*>(w);
  vtkResliceCursorRepresentation *rep =
    reinterpret_cast<vtkResliceCursorRepresentation*>(self->WidgetRep);

  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];

  self->ModifierActive = vtkEvent::GetModifier(self->Interactor);
  rep->ComputeInteractionState(X, Y, self->ModifierActive);

  if ( self->WidgetRep->GetInteractionState()
      == vtkResliceCursorRepresentation::Outside )
    {
    return;
    }

  rep->SetManipulationMode(vtkResliceCursorRepresentation::RotateBothAxes);

  self->GrabFocus(self->EventCallbackCommand);
  double eventPos[2];
  eventPos[0] = static_cast<double>(X);
  eventPos[1] = static_cast<double>(Y);
  self->WidgetRep->StartWidgetInteraction(eventPos);


  self->WidgetState = vtkResliceCursorWidget::Active;
  self->SetCursor(self->WidgetRep->GetInteractionState());


  self->WidgetRep->Highlight(1);

  self->EventCallbackCommand->SetAbortFlag(1);
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
  self->Render();

  self->InvokeAnEvent();
}
