RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkImageData *inData = vtkImageData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkImageData *outData = vtkImageData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
  int extent[6];


  inData->GetExtent(extent);
  for (int i = 0; i < 3; ++i)
    {
    extent[i*2] += this->Translation[i];
    extent[i*2+1] += this->Translation[i];
    }
  outData->SetExtent(extent);
  outData->GetPointData()->PassData(inData->GetPointData());

  return 1;
}
