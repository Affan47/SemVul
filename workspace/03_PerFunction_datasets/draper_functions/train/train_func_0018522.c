SetEnabled(int enabling)
{
  if ( ! this->Interactor )
    {
    vtkErrorMacro(<<"The interactor must be set prior to enabling/disabling widget");
    return;
    }

  if ( enabling )
    {
    vtkDebugMacro(<<"Enabling sphere widget");

    if ( this->Enabled )
      {
      return;
      }

    if ( ! this->CurrentRenderer )
      {
      this->SetCurrentRenderer(
        this->Interactor->FindPokedRenderer(
          this->Interactor->GetLastEventPosition()[0],
          this->Interactor->GetLastEventPosition()[1]));
      if (this->CurrentRenderer == NULL)
        {
        return;
        }
      }

    this->Enabled = 1;


    vtkRenderWindowInteractor *i = this->Interactor;
    i->AddObserver(vtkCommand::MouseMoveEvent,
                   this->EventCallbackCommand, this->Priority);
    i->AddObserver(vtkCommand::LeftButtonPressEvent,
                   this->EventCallbackCommand, this->Priority);
    i->AddObserver(vtkCommand::LeftButtonReleaseEvent,
                   this->EventCallbackCommand, this->Priority);
    i->AddObserver(vtkCommand::RightButtonPressEvent,
                   this->EventCallbackCommand, this->Priority);
    i->AddObserver(vtkCommand::RightButtonReleaseEvent,
                   this->EventCallbackCommand, this->Priority);


    this->CurrentRenderer->AddActor(this->SphereActor);
    this->SphereActor->SetProperty(this->SphereProperty);

    this->CurrentRenderer->AddActor(this->HandleActor);
    this->HandleActor->SetProperty(this->HandleProperty);
    this->SelectRepresentation();
    this->SizeHandles();

    this->InvokeEvent(vtkCommand::EnableEvent,NULL);
    }

  else
    {
    vtkDebugMacro(<<"Disabling sphere widget");

    if ( ! this->Enabled )
      {
      return;
      }

    this->Enabled = 0;


    this->Interactor->RemoveObserver(this->EventCallbackCommand);


    this->CurrentRenderer->RemoveActor(this->SphereActor);
    this->CurrentRenderer->RemoveActor(this->HandleActor);

    this->InvokeEvent(vtkCommand::DisableEvent,NULL);
    this->SetCurrentRenderer(NULL);
    }

  this->Interactor->Render();
}
