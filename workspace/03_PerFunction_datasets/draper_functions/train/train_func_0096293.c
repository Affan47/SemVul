RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector ** vtkNotUsed( inputVector ),
  vtkInformationVector *outputVector)
{

  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  int i;
  double ar[3], origin[3];

  int wExt[6];
  wExt[0] = 0; wExt[2] = 0; wExt[4] = 0;
  wExt[1] = this->SampleDimensions[0]-1;
  wExt[3] = this->SampleDimensions[1]-1;
  wExt[5] = this->SampleDimensions[2]-1;

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wExt, 6);

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

  vtkDataObject::SetPointDataActiveScalarInfo(outInfo,this->OutputScalarType,
                                              1);

  return 1;
}
