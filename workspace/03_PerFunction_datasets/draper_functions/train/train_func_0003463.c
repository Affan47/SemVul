SetEnabled(int enabling)
{
  if ( this->Interactor )
    {
    this->Interactor->Disable();
    }

  if ( enabling )
    {
    this->CreateDefaultRepresentation();
    this->HandleWidget->SetRepresentation(reinterpret_cast<vtkCaptionRepresentation*>
                                          (this->WidgetRep)->GetAnchorRepresentation());
    this->HandleWidget->SetInteractor(this->Interactor);
    this->HandleWidget->SetEnabled(1);
    }
  else
    {
    this->HandleWidget->SetEnabled(0);
    }
  if ( this->Interactor )
    {
    this->Interactor->Enable();
    }

  this->Superclass::SetEnabled(enabling);
}
