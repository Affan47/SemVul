ThreadedExecute (vtkImageData *inData,
                                       vtkImageData *outData,
                                       int outExt[6], int id)
{
  vtkDebugMacro(<< "Execute: inData = " << inData
                << ", outData = " << outData);


  if (inData->GetScalarType() != outData->GetScalarType())
    {
    vtkErrorMacro(<< "Execute: input ScalarType, "
                  << inData->GetScalarType()
                  << ", must match out ScalarType "
                  << outData->GetScalarType());
    return;
    }


  if (inData->GetNumberOfScalarComponents() < 2)
    {
    vtkErrorMacro(<< "Execute: input does not have at least two components");
    return;
    }

  switch (inData->GetScalarType())
    {
    vtkTemplateMacro(
      vtkImageEuclideanToPolarExecute( this,
                                       inData, outData, outExt, id,
                                       static_cast<VTK_TT *>(0)));
    default:
      vtkErrorMacro(<< "Execute: Unknown ScalarType");
      return;
    }
}
