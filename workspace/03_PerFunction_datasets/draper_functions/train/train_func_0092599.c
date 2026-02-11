MoveAction(vtkAbstractWidget *w)
{
  vtkButtonWidget *self = reinterpret_cast<vtkButtonWidget*>(w);

  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  if ( self->WidgetState == vtkButtonWidget::Selecting )
    {
    self->EventCallbackCommand->SetAbortFlag(1);
    return;
    }


  int renderRequired = 0;
  int state = self->WidgetRep->ComputeInteractionState(X, Y);
  if ( self->WidgetState == vtkButtonWidget::Hovering )
    {
    if ( state == vtkButtonRepresentation::Outside )
      {
      renderRequired = 1;
      if ( self->ManagesCursor )
        {
        self->RequestCursorShape(VTK_CURSOR_DEFAULT);
        }
      self->WidgetRep->Highlight(vtkButtonRepresentation::HighlightNormal);
      self->WidgetState = vtkButtonWidget::Start;
      }
    }
  else
    {
    if ( state == vtkButtonRepresentation::Inside )
      {
      renderRequired = 1;
      if ( self->ManagesCursor )
        {
        self->RequestCursorShape(VTK_CURSOR_HAND);
        }
      self->WidgetRep->Highlight(vtkButtonRepresentation::HighlightHovering);
      self->WidgetState = vtkButtonWidget::Hovering;
      self->EventCallbackCommand->SetAbortFlag(1);
      }
    }

  if ( renderRequired )
    {
    self->Render();
    }
}
