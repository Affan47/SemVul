SetHandleHighlight(
                      int handleIdx, vtkProperty *property )
{
  if ( handleIdx == -1)
    {

    for (int i = 0; i < 8; i++)
      {
      static_cast< vtkSphereHandleRepresentation * >(
          this->HandleRepresentations[i])->SetProperty(property);
      static_cast< vtkSphereHandleRepresentation * >(
          this->HandleRepresentations[i])->SetSelectedProperty(property);
      }
    }
  else
    {
    static_cast< vtkSphereHandleRepresentation * >(
        this->HandleRepresentations[handleIdx])->SetProperty(property);
    static_cast< vtkSphereHandleRepresentation * >(
        this->HandleRepresentations[handleIdx])->SetSelectedProperty(property);
    }
}
