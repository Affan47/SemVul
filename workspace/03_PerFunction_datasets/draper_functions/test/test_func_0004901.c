SetEnabled(int enabling)
{
  if ( !this->Interactor )
    {
    vtkErrorMacro(<<"The interactor must be set prior to enabling/disabling widget");
    return;
    }

  if ( !this->ViewProp )
    {
    vtkErrorMacro(<<"The external prop must be set prior to enabling/disabling widget");
    return;
    }

  if ( enabling )
    {
    vtkDebugMacro(<<"Enabling line widget");

    if ( this->Enabled )
      {
      return;
      }

    if ( !this->CurrentRenderer )
      {
      this->SetCurrentRenderer(this->Interactor->FindPokedRenderer(
                               this->Interactor->GetLastEventPosition()[0],
                               this->Interactor->GetLastEventPosition()[1]));
      if ( !this->CurrentRenderer )
        {
        return;
        }
      }

    this->Enabled = 1;

    this->AddObservers();


    for ( int i = 0; i < this->NumberOfHandles; ++i )
      {
      this->CurrentRenderer->AddViewProp(this->Handle[i]);
      this->Handle[i]->SetProperty(this->HandleProperty);
      this->Handle[i]->PickableOff();
      }

    this->SizeHandles();

    this->CurrentRenderer->AddViewProp(this->LineActor);
    this->LineActor->SetProperty(this->LineProperty);
    this->LineActor->PickableOff();

    this->InvokeEvent(vtkCommand::EnableEvent,NULL);
    }

  else
    {
    vtkDebugMacro(<<"Disabling tracer widget");

    if ( !this->Enabled )
      {
      return;
      }


    if ( this->State == vtkImageTracerWidget::Tracing )
      {
      this->OnLeftButtonUp();
      }
    else if ( this->State == vtkImageTracerWidget::Snapping )
      {
      this->Interactor->SetControlKey( 1 );
      this->OnMiddleButtonUp();
      }

    this->Enabled = 0;


    this->Interactor->RemoveObserver(this->EventCallbackCommand);


    for ( int i = 0; i < this->NumberOfHandles; ++i )
     {
     this->CurrentRenderer->RemoveViewProp(this->Handle[i]);
     }

    this->CurrentRenderer->RemoveViewProp(this->LineActor);

    this->CurrentHandle = NULL;
    this->InvokeEvent(vtkCommand::DisableEvent,NULL);
    this->SetCurrentRenderer(NULL);
    }

  this->Interactor->Render();
}
