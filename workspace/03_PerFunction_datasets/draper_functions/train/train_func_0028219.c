RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  int wholeMin, wholeMax, axis, ext[6];
  double spacing[3], factor;

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), ext);
  inInfo->Get(vtkDataObject::SPACING(), spacing);

  for (axis = 0; axis < 3; axis++)
    {
    wholeMin = ext[axis*2];
    wholeMax = ext[axis*2+1];


    factor = 1.0;
    if (axis < this->Dimensionality)
      {
      factor = this->GetAxisMagnificationFactor(axis, inInfo);
      }

    wholeMin = static_cast<int>(ceil(static_cast<double>(wholeMin) * factor));
    wholeMax = static_cast<int>(floor(static_cast<double>(wholeMax) * factor));


    spacing[axis] /= factor;

    ext[axis*2] = wholeMin;
    ext[axis*2+1] = wholeMax;


    if (this->OutputSpacing[axis] != 0.0)
      {

      this->MagnificationFactors[axis] = 0.0;
      }
    }

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), ext, 6);
  outInfo->Set(vtkDataObject::SPACING(), spacing, 3);

  return 1;
}
