RequestResizeAlongAnAxisCallback(vtkAbstractWidget *w)
{
  vtkParallelopipedWidget *self = reinterpret_cast<vtkParallelopipedWidget*>(w);
  vtkParallelopipedRepresentation *rep =
    reinterpret_cast<vtkParallelopipedRepresentation*>(self->WidgetRep);

  const int modifier = self->Interactor->GetShiftKey()   |
                       self->Interactor->GetControlKey() |
                       self->Interactor->GetAltKey();


  rep->SetInteractionState(
    vtkParallelopipedRepresentation::RequestResizeParallelopipedAlongAnAxis );


  int interactionState = rep->ComputeInteractionState(
      self->Interactor->GetEventPosition()[0],
      self->Interactor->GetEventPosition()[1], modifier );

  self->SetCursor(interactionState);

  if (interactionState == vtkParallelopipedRepresentation::Inside)
    {


    self->TranslateCallback( self );
    }

  else if (interactionState != vtkParallelopipedRepresentation::Outside)
    {
    self->EventCallbackCommand->SetAbortFlag(1);
    self->StartInteraction();
    self->InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
    self->Interactor->Render();
    }
}
