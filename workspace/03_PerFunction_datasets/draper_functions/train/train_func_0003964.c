HighlightHandle(vtkProp *prop)
{

  this->HighlightOutline(0);
  if ( this->CurrentHandle )
    {
    this->CurrentHandle->SetProperty(this->HandleProperty);
    }

  this->CurrentHandle = static_cast<vtkActor *>(prop);

  if ( this->CurrentHandle )
    {
    this->CurrentHandle->SetProperty(this->SelectedHandleProperty);
    for (int i=0; i<6; i++)
      {
      if ( this->CurrentHandle == this->Handle[i] )
        {
        return i;
        }
      }
    }

  if ( this->CurrentHandle == this->Handle[6] )
    {
    this->HighlightOutline(1);
    }

  return -1;
}
