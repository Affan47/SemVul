RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector ** vtkNotUsed( inputVector ),
  vtkInformationVector *outputVector)
{

  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  int i;
  double ar[3], origin[3];

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               0, this->SampleDimensions[0]-1,
               0, this->SampleDimensions[1]-1,
               0, this->SampleDimensions[2]-1);

  for (i=0; i < 3; i++)
    {
    origin[i] = this->ModelBounds[2*i];
    if ( this->SampleDimensions[i] <= 1 )
      {
      ar[i] = 1;
      }
    else
      {
      ar[i] = (this->ModelBounds[2*i+1] - this->ModelBounds[2*i])
              / (this->SampleDimensions[i] - 1);
      }
    }
  outInfo->Set(vtkDataObject::ORIGIN(),origin,3);
  outInfo->Set(vtkDataObject::SPACING(),ar,3);

  vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_FLOAT, 1);
  return 1;
}
