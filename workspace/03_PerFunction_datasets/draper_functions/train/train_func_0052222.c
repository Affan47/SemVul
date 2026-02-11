RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed( inputVector ),
  vtkInformationVector *outputVector)
{
  if (this->Input == NULL )
    {
    vtkErrorMacro(<<"Please specify a renderer as input!");
    return;
    }

  if(this->Magnification > 1 &&
     (this->Viewport[0] != 0 || this->Viewport[1] != 0 ||
      this->Viewport[2] != 1 || this->Viewport[3] != 1))
    {
    vtkWarningMacro(<<"Viewport extents are not used when Magnification > 1");
    this->Viewport[0] = 0;
    this->Viewport[1] = 0;
    this->Viewport[2] = 1;
    this->Viewport[3] = 1;
    }


  int *size = this->Input->GetSize();
  int wExtent[6];
  wExtent[0]= 0;
  wExtent[1] = (int(this->Viewport[2] * size[0] + 0.5)-
    int(this->Viewport[0] * size[0])) * this->Magnification - 1;
  wExtent[2] = 0;
  wExtent[3] = (int(this->Viewport[3] * size[1] + 0.5)-
    int(this->Viewport[1] * size[1])) * this->Magnification - 1;
  wExtent[4] = 0;
  wExtent[5] = 0;


  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wExtent, 6);

  switch( this->InputBufferType )
    {
    case VTK_RGB:
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 3);
      break;
    case VTK_RGBA:
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 4);
      break;
    case VTK_ZBUFFER:
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_FLOAT, 1);
      break;
    default:

      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 3);
      break;
    }
}
