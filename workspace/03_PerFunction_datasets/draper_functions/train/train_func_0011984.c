ThreadedRequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector,
  vtkImageData ***inData,
  vtkImageData **outData,
  int outExt[6], int id)
{
  void *inPtr, *inPtr2;
  void *outPtr;
  vtkImageData *inData2 = this->GetBackgroundInput();

  inPtr = inData[0][0]->GetScalarPointer();
  outPtr = outData[0]->GetScalarPointerForExtent(outExt);

  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  inPtr2 = NULL;
  if (inData2)
    {
    inPtr2 = inData2->GetScalarPointer();
    if (inData2->GetScalarType() != inData[0][0]->GetScalarType())
      {
      if (id == 0)
        {
        vtkErrorMacro("Execute: BackgroundInput ScalarType "
                      << inData2->GetScalarType()
                      << ", must match Input ScalarType "
                      << inData[0][0]->GetScalarType());
        }
      return;
      }
    else if (inData2->GetNumberOfScalarComponents()
             != inData[0][0]->GetNumberOfScalarComponents())
      {
      if (id == 0)
        {
        vtkErrorMacro("Execute: BackgroundInput NumberOfScalarComponents "
                      << inData2->GetNumberOfScalarComponents()
                      << ", must match Input NumberOfScalarComponents "
                      << inData[0][0]->GetNumberOfScalarComponents());
        }
      return;
      }
    int wholeExt1[6], wholeExt2[6];
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
    vtkInformation *inInfo2 = inputVector[1]->GetInformationObject(0);
    inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),wholeExt1);
    inInfo2->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),wholeExt2);

    for (int i = 0; i < 6; i++)
      {
      if (wholeExt1[i] != wholeExt2[i])
        {
        if (id == 0)
          {
          vtkErrorMacro("Execute: BackgroundInput must have the same "
                        "WholeExtent as the Input");
          }
        return;
        }
      }
    }

  switch (inData[0][0]->GetScalarType())
    {
    vtkTemplateMacro(
      vtkImageStencilExecute(this,
                             inData[0][0],
                             static_cast<VTK_TT *>(inPtr),
                             inData2,
                             static_cast<VTK_TT *>(inPtr2),
                             outData[0],
                             static_cast<VTK_TT *>(outPtr),
                             outExt,
                             id,
                             outInfo));
    default:
      vtkErrorMacro("Execute: Unknown ScalarType");
      return;
    }
}
