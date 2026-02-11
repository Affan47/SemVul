Disable()
{
  if (!this->Enabled)
    {
    return;
    }

  this->Enabled = 0;


  if (this->Top)
    {
    XtRemoveEventHandler(this->Top,
                        KeyPressMask | KeyReleaseMask | ButtonPressMask |
                        ExposureMask | ButtonReleaseMask |
                        EnterWindowMask | LeaveWindowMask |
                        PointerMotionHintMask | PointerMotionMask,
                        True,vtkXRenderWindowInteractorCallback,
                        static_cast<XtPointer>(this));
    }

  this->Modified();
}
