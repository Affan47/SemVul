CopyStructure(vtkFieldData* r)
{

  this->InitializeFields();


  this->AllocateArrays(r->GetNumberOfArrays());
  this->NumberOfActiveArrays = r->GetNumberOfArrays();


  int i;
  vtkAbstractArray* data;
  for(i=0; i < r->GetNumberOfArrays(); ++i)
    {
    data = r->Data[i]->NewInstance();
    data->SetNumberOfComponents(r->Data[i]->GetNumberOfComponents());
    data->SetName(r->Data[i]->GetName());
    if (r->Data[i]->HasInformation())
      {
      data->CopyInformation(r->Data[i]->GetInformation(),1);
      }
    this->SetArray(i, data);
    data->Delete();
    }
}
