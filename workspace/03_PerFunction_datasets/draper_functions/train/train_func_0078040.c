SetInteraction(int interact)
{
  if ( this->Interactor && this->Enabled )
    {
    if ( this->Interaction == interact )
      {
      return;
      }
    if ( interact == 0 )
      {
      this->Interactor->RemoveObserver(this->EventCallbackCommand);
      }
    else
      {
      this->AddObservers();
      }
    this->Interaction = interact;
    }
  else
    {
    vtkGenericWarningMacro(<<"Set interactor and Enabled before changing interaction...");
    }
}
