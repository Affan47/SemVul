ShallowCopy(vtkProp *prop)
{
  vtkAffineRepresentation2D *rep =
    vtkAffineRepresentation2D::SafeDownCast(prop);
  if ( rep )
    {
    this->SetProperty(rep->GetProperty());
    this->SetSelectedProperty(rep->GetSelectedProperty());
    this->SetTextProperty(rep->GetTextProperty());
    this->BoxActor->SetProperty(this->Property);
    this->HBoxActor->SetProperty(this->SelectedProperty);
    this->CircleActor->SetProperty(this->Property);
    this->HCircleActor->SetProperty(this->SelectedProperty);
    this->XAxis->SetProperty(this->Property);
    this->YAxis->SetProperty(this->Property);
    this->HXAxis->SetProperty(this->SelectedProperty);
    this->HYAxis->SetProperty(this->SelectedProperty);
    }
  this->Superclass::ShallowCopy(prop);
}
