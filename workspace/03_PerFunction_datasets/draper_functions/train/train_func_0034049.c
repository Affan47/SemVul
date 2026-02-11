Get(vtkInformation* info,
                                               vtkExecutive** executives,
                                               int* ports)
{
  if(vtkInformationExecutivePortVectorValue* v =
     static_cast<vtkInformationExecutivePortVectorValue *>
     (this->GetAsObjectBase(info)))
    {
    std::copy(v->Executives.begin(), v->Executives.end(), executives);
    std::copy(v->Ports.begin(), v->Ports.end(), ports);
    }
}
