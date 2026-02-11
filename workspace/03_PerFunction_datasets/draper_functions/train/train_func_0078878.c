RequestData(
  vtkInformation* vtkNotUsed( request ),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkImageData *output = vtkImageData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkImageData *input = vtkImageData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));

  int inExt[6];
  input->GetExtent(inExt);

  if (inExt[1] < inExt[0] ||
      inExt[3] < inExt[2] ||
      inExt[5] < inExt[4])
    {
    return 1;
    }


  output->SetExtent(
    outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT()));
  output->AllocateScalars();

  this->SimpleExecute(input, output);

  return 1;
}
