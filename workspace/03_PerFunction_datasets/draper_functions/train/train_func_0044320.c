SetArrayName(const char* name)
{
  if (!this->ArrayNames)
    {
    this->ArrayNames = vtkStringArray::New();
    }
  this->ArrayNames->Initialize();
  this->ArrayNames->InsertNextValue(name);
}
