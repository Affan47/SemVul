RequestInformation(
  vtkInformation *, vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  int extent[6];
  int range[2];
  double origin[3];
  double spacing[3];
  double sliceSpacing;
  int dimIndex;
  int scalarType;

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  inInfo->Get(vtkDataObject::SPACING(), spacing);
  inInfo->Get(vtkDataObject::ORIGIN(), origin);


  dimIndex = this->GetOrientation();


  this->GetSliceRange(range);
  if (range[0] < extent[2*dimIndex])
    {
    range[0] = extent[2*dimIndex];
    }
  if (range[1] > extent[2*dimIndex+1])
    {
    range[1] = extent[2*dimIndex+1];
    }


  sliceSpacing = spacing[dimIndex];
  origin[dimIndex] = (origin[dimIndex] +
                      0.5*sliceSpacing*(range[0] + range[1]));

  if (this->GetMultiSliceOutput())
    {

    extent[2*dimIndex] -= range[0];
    extent[2*dimIndex+1] -= range[1];
    }
  else
    {

    extent[2*dimIndex] = 0;
    extent[2*dimIndex+1] = 0;
    }


  scalarType = this->GetOutputScalarType();


  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
    extent, 6);
  outInfo->Set(vtkDataObject::SPACING(), spacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(), origin, 3);


  if (scalarType == VTK_FLOAT || scalarType == VTK_DOUBLE)
    {
    vtkDataObject::SetPointDataActiveScalarInfo(outInfo, scalarType, -1);
    }

  return 1;
}
