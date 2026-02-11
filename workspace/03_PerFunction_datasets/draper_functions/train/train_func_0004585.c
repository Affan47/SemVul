RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkDataSet *input = vtkDataSet::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkDataSet *output = vtkDataSet::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));


  output->CopyStructure( input );


  output->GetPointData()->PassData( input->GetPointData() );
  output->GetCellData()->PassData( input->GetCellData() );

  vtkDataArray* outputArray;
  vtkDataArray* inputArray = 0;
  vtkFieldData* fd = 0;
  vtkFieldData* outputFD = 0;
  Component* cur = this->GetFirst();
  Component* before;

  if (!cur) { return 1; }


  if ( this->FieldLocation == vtkSplitField::DATA_OBJECT)
    {
    fd = input->GetFieldData();
    outputFD = output->GetFieldData();
    if (!fd || !outputFD)
      {
      vtkErrorMacro("No field data in vtkDataObject.");
      return 1;
      }
    }
  else if ( this->FieldLocation == vtkSplitField::POINT_DATA )
    {
    fd = input->GetPointData();
    outputFD = output->GetPointData();
    }
  else if ( this->FieldLocation == vtkSplitField::CELL_DATA )
    {
    fd = input->GetCellData();
    outputFD = output->GetCellData();
    }

  if ( this->FieldType == vtkSplitField::NAME )
    {
    inputArray = fd->GetArray(this->FieldName);
    }
  else if ( this->FieldType == vtkSplitField::ATTRIBUTE )
    {


    vtkDataSetAttributes* dsa=vtkDataSetAttributes::SafeDownCast(fd);
    if (!dsa)
      {
      vtkErrorMacro("Sanity check failed, returning.");
      return 1;
      }
    inputArray = dsa->GetAttribute(this->AttributeType);
    }

  if (!inputArray)
    {
    vtkErrorMacro("Sanity check failed, returning.");
    return 1;
    }


  do
    {
    before = cur;
    cur = cur->Next;
    if (before->FieldName)
      {
      outputArray = this->SplitArray(inputArray, before->Index);
      if (outputArray)
        {
        outputArray->SetName(before->FieldName);
        outputFD->AddArray(outputArray);
        outputArray->UnRegister(this);
        }
      }
    }
  while (cur);

  return 1;
}
