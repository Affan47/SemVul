RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int idx, extent[6];
  double spacing[3], origin[3];

  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),extent);
  inInfo->Get(vtkDataObject::ORIGIN(), origin);
  inInfo->Get(vtkDataObject::SPACING(), spacing);


  for (idx = 0; idx < 3; ++idx)
    {

    extent[2*idx] += this->Translation[idx];
    extent[2*idx+1] += this->Translation[idx];

    origin[idx] -= static_cast<double>(this->Translation[idx]) * spacing[idx];
    }

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),extent,6);
  outInfo->Set(vtkDataObject::ORIGIN(),origin,3);

  return 1;
}
