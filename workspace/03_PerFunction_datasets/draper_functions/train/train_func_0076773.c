GetTypeAsString() const
{
  if (this->Type == VTK_OBJECT && this->Valid)
    {
    return this->Data.VTKObject->GetClassName();
    }
  return vtkImageScalarTypeNameMacro(this->Type);
}
