Get(vtkInformation* info)
{
  vtkInformationStringValue* v =
    static_cast<vtkInformationStringValue *>(this->GetAsObjectBase(info));
  return v?v->Value.c_str():0;
}
