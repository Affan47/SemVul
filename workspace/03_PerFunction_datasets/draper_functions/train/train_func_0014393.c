CopyIntoArrayComponent(vtkDataArray *array, int component)
{
  vtkIdType i;

  if (array==NULL)
    {
    vtkErrorMacro(<<"NULL vtkDoubleArray provided!");
    return;
    }

  if (component > array->GetNumberOfComponents()-1)
    {
    array->SetNumberOfComponents(component+1);
    }

  if (this->NumberOfElements>array->GetNumberOfTuples())
    {
    array->SetNumberOfTuples(this->NumberOfElements);
    }

  for (i=0; i<this->NumberOfElements; i++)
    {
    array->SetComponent(i,component,this->Array[i]);
    }
}
