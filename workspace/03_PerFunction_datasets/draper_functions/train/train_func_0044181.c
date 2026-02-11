ProcessRequest(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{

  if(request->Has(vtkCompositeDataPipeline::REQUEST_DATA()))
    {
    int retVal = this->RequestCompositeData(request, inputVector, outputVector);
    return retVal;
    }

 return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}
