OnRightButtonUp()
{
  switch (this->State)
    {
    case VTKIS_USCALE:
      this->EndUniformScale();
      break;
    }

  if ( this->Interactor )
    {
    this->ReleaseFocus();
    }
}
