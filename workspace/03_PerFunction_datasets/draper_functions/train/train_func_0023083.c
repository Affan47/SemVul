RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{

  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkUnstructuredGrid *output = vtkUnstructuredGrid::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkDebugMacro( << "Reading AVS UCD file");


  if ( this->FileStream )
    {
    this->ReadFile(output);
    }

  return 1;
}
