OnMiddleButtonUp()
{
  if ( this->State == vtkImageTracerWidget::Outside ||
       this->State == vtkImageTracerWidget::Start )
    {
    return;
    }

  if ( this->Interactor->GetControlKey() )
    {
    this->IsSnapping = 0;
    }
  else
    {
    return;
    }

  this->State = vtkImageTracerWidget::Start;
  this->CurrentHandleIndex = this->HighlightHandle(NULL);

  if ( this->AutoClose )
    {
    this->ClosePath();
    if ( this->IsClosed() )
      {
      this->EraseHandle(this->NumberOfHandles - 1);
      }
    }

  this->SizeHandles();

  this->EventCallbackCommand->SetAbortFlag(1);
  this->EndInteraction();
  this->InvokeEvent(vtkCommand::EndInteractionEvent,NULL);
  this->Interactor->Render();
  this->CurrentPicker = NULL;
}
