Set(vtkInformation* info, int* value,
                                          int length)
{
  if(value)
    {
    if(this->RequiredLength >= 0 && length != this->RequiredLength)
      {
      vtkErrorWithObjectMacro(
        info,
        "Cannot store integer vector of length " << length
        << " with key " << this->Location << "::" << this->Name
        << " which requires a vector of length "
        << this->RequiredLength << ".  Removing the key instead.");
      this->SetAsObjectBase(info, 0);
      return;
      }


    vtkInformationIntegerPointerValue* v =
      new vtkInformationIntegerPointerValue;
    this->ConstructClass("vtkInformationIntegerPointerValue");
    v->Value = value;
    v->Length = length;
    this->SetAsObjectBase(info, v);
    v->Delete();
    }
  else
    {
    this->SetAsObjectBase(info, 0);
    }
}
