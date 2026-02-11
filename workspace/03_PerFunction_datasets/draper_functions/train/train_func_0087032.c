RequestInformation(vtkInformation *request,
                                          vtkInformationVector **inputVector,
                                          vtkInformationVector *outputVector)
{

  if (!this->Superclass::RequestInformation(request, inputVector, outputVector))
    {
    return 0;
    }


  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkDataObject *output = vtkDataObject::GetData(outInfo);
  if (output && (output->GetExtentType() != VTK_3D_EXTENT))
    {
    outInfo->Set(
              vtkStreamingDemandDrivenPipeline::MAXIMUM_NUMBER_OF_PIECES(), -1);
    }

  return 1;
}
