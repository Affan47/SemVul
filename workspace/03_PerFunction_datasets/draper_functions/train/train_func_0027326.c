TranslateAction(vtkAbstractWidget *w)
{
  vtkHandleWidget *self = reinterpret_cast<vtkHandleWidget*>(w);

  double eventPos[2];
  eventPos[0] = static_cast<double>(self->Interactor->GetEventPosition()[0]);
  eventPos[1] = static_cast<double>(self->Interactor->GetEventPosition()[1]);

  self->WidgetRep->StartWidgetInteraction(eventPos);
  if ( self->WidgetRep->GetInteractionState() == vtkHandleRepresentation::Outside )
    {
    return;
    }


  self->WidgetState = vtkHandleWidget::Active;
  reinterpret_cast<vtkHandleRepresentation*>(self->WidgetRep)->
    SetInteractionState(vtkHandleRepresentation::Translating);

  self->GenericAction(self);
}
