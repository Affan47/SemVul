EndSelectAction(vtkAbstractWidget *w)
{
  vtkContinuousValueWidget *self =
    reinterpret_cast<vtkContinuousValueWidget*>(w);

  if ( self->WidgetState != vtkContinuousValueWidget::Adjusting )
    {
    return;
    }

  int interactionState = self->WidgetRep->ComputeInteractionState
    (self->Interactor->GetEventPosition()[0],
     self->Interactor->GetEventPosition()[1]);
  if ( interactionState == vtkContinuousValueWidgetRepresentation::Outside)
    {
    self->WidgetRep->Highlight(0);
    self->WidgetState = vtkContinuousValueWidget::Start;
    }
  else
    {
    self->WidgetState = vtkContinuousValueWidget::Highlighting;
    }


  self->ReleaseFocus();


  self->EventCallbackCommand->SetAbortFlag(1);
  self->EndInteraction();
  self->InvokeEvent(vtkCommand::EndInteractionEvent,NULL);
  self->Render();
}
