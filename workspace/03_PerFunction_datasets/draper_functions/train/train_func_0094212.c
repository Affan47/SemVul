GenericAction(vtkHandleWidget *self)
{


  self->SetCursor(self->WidgetRep->GetInteractionState());


  if ( self->Interactor->GetShiftKey() && self->EnableAxisConstraint )
    {
    reinterpret_cast<vtkHandleRepresentation*>(self->WidgetRep)->ConstrainedOn();
    }
  else
    {
    reinterpret_cast<vtkHandleRepresentation*>(self->WidgetRep)->ConstrainedOff();
    }


  self->WidgetRep->Highlight(1);

  self->EventCallbackCommand->SetAbortFlag(1);
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
  self->Render();
}
