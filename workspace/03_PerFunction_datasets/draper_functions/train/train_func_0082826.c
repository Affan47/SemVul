ProcessEvent(vtkRenderer *renderer,
                                         unsigned long event,
                                         void *calldata)
{
  vtkDebugMacro(<<"vtkTDxInteractorStyle::ProcessEvent()");
  this->Renderer=renderer;

  vtkTDxMotionEventInfo *motionInfo;
  int *buttonInfo;

  switch(event)
    {
    case vtkCommand::TDxMotionEvent:
      vtkDebugMacro(<<"vtkTDxInteractorStyle::ProcessEvent() TDxMotionEvent");
      motionInfo=static_cast<vtkTDxMotionEventInfo *>(calldata);
      this->OnMotionEvent(motionInfo);
      break;
    case vtkCommand::TDxButtonPressEvent:
      vtkDebugMacro(<<"vtkTDxInteractorStyle::ProcessEvent() TDxButtonPressEvent");
      buttonInfo=static_cast<int *>(calldata);
      this->OnButtonPressedEvent(*buttonInfo);
      break;
    case vtkCommand::TDxButtonReleaseEvent:
      vtkDebugMacro(<<"vtkTDxInteractorStyle::ProcessEvent() TDxButtonReleaseEvent");
      buttonInfo=static_cast<int *>(calldata);
      this->OnButtonReleasedEvent(*buttonInfo);
      break;
    }
}
