ShallowCopy(vtkProp *prop)
{
  vtkAxisActor2D *a = vtkAxisActor2D::SafeDownCast(prop);
  if ( a != NULL )
    {
    this->SetRange(a->GetRange());
    this->SetNumberOfLabels(a->GetNumberOfLabels());
    this->SetLabelFormat(a->GetLabelFormat());
    this->SetAdjustLabels(a->GetAdjustLabels());
    this->SetTitle(a->GetTitle());
    this->SetTickLength(a->GetTickLength());
    this->SetTickOffset(a->GetTickOffset());
    this->SetAxisVisibility(a->GetAxisVisibility());
    this->SetTickVisibility(a->GetTickVisibility());
    this->SetLabelVisibility(a->GetLabelVisibility());
    this->SetTitleVisibility(a->GetTitleVisibility());
    this->SetFontFactor(a->GetFontFactor());
    this->SetLabelFactor(a->GetLabelFactor());
    this->SetLabelTextProperty(a->GetLabelTextProperty());
    this->SetTitleTextProperty(a->GetTitleTextProperty());
    }


  this->vtkActor2D::ShallowCopy(prop);
}
