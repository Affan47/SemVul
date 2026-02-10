SetEnabled(int enabling)
{

  if ( enabling )
    {

    if ( ! this->CurrentRenderer )
      {
      int X=this->Interactor->GetEventPosition()[0];
      int Y=this->Interactor->GetEventPosition()[1];

      this->SetCurrentRenderer(this->Interactor->FindPokedRenderer(X,Y));

      if (this->CurrentRenderer == NULL)
        {
        return;
        }
      }


    this->CreateDefaultRepresentation();
    vtkHandleRepresentation * originRep = reinterpret_cast<vtkAxesTransformRepresentation*>
                                          (this->WidgetRep)->GetOriginRepresentation();
    originRep->SetRenderer(this->CurrentRenderer);
    this->OriginWidget->SetRepresentation(originRep);
    this->OriginWidget->SetInteractor(this->Interactor);

    vtkHandleRepresentation * selectionRep = reinterpret_cast<vtkAxesTransformRepresentation*>
                                          (this->WidgetRep)->GetSelectionRepresentation();
    selectionRep->SetRenderer(this->CurrentRenderer);
    this->SelectionWidget->SetRepresentation(selectionRep);
    this->SelectionWidget->SetInteractor(this->Interactor);


    this->Superclass::SetEnabled(enabling);
    }
  else
    {
    this->OriginWidget->SetEnabled(0);
    this->SelectionWidget->SetEnabled(0);
    }
}
