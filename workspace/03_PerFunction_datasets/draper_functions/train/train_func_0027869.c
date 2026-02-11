GetInputArrayFieldInformation(int idx, vtkInformationVector **inputVector)
{

  vtkInformation *info = this->GetInputArrayInformation(idx);


  int port = info->Get(INPUT_PORT());
  int connection = info->Get(INPUT_CONNECTION());
  int fieldAssoc = info->Get(vtkDataObject::FIELD_ASSOCIATION());
  vtkInformation *inInfo = inputVector[port]->GetInformationObject(connection);

  if (info->Has(vtkDataObject::FIELD_NAME()))
    {
    const char *name = info->Get(vtkDataObject::FIELD_NAME());
    return vtkDataObject::GetNamedFieldInformation(inInfo, fieldAssoc, name);
    }
  int fType = info->Get(vtkDataObject::FIELD_ATTRIBUTE_TYPE());
  return vtkDataObject::GetActiveFieldInformation(inInfo, fieldAssoc, fType);
}
