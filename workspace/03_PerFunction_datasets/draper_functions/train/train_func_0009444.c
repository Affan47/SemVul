Execute(
    vtkObject *caller, unsigned long eventId, void *callData)
    {
    if (this->Callable)
      {
      this->AbortFlagOff();
      if((*this->Callable)(caller, eventId, callData))
        {
        this->AbortFlagOn();
        }
      }
    }
