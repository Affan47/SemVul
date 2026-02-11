RequestUpdateExtent(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  if (this->PropagateUpdateExtentCallback)
    {
    int uExt[6];

    vtkInformation* outInfo = outputVector->GetInformationObject(0);
    outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),uExt);
    tryCatchMacro(
      (this->PropagateUpdateExtentCallback)(this->CallbackUserData,uExt),
      "PropagateUpdateExtentCallback: ");
    }

  return 1;
}
