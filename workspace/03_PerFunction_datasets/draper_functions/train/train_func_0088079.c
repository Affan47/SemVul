Get(vtkInformation* info,
                                     double* value)
{
  vtkInformationDoubleVectorValue* v =
    static_cast<vtkInformationDoubleVectorValue *>(
      this->GetAsObjectBase(info));
  if(v && value)
    {
    for(std::vector<double>::size_type i = 0;
        i < v->Value.size(); ++i)
      {
      value[i] = v->Value[i];
      }
    }
}
