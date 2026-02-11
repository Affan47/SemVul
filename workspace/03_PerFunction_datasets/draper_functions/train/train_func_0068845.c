ThreadedRequestData(vtkInformation*,
                                           vtkInformationVector** inputVector,
                                           vtkInformationVector*,
                                           vtkImageData*** inData,
                                           vtkImageData** outData,
                                           int outExt[6],
                                           int threadId)
{

  vtkImageData* input = inData[0][0];
  vtkImageData* output = outData[0];


  if(output->GetScalarType() != VTK_DOUBLE)
    {
    vtkErrorMacro("Execute: output ScalarType is "
                  << output->GetScalarType() << "but must be double.");
    return;
    }

  vtkDataArray* inputArray = this->GetInputArrayToProcess(0, inputVector);
  if (!inputArray)
    {
    vtkErrorMacro("No input array was found. Cannot execute");
    return;
    }


  if(inputArray->GetNumberOfComponents() != 1)
    {
    vtkErrorMacro(
      "Execute: input has more than one component. "
      "The input to gradient should be a single component image. "
      "Think about it. If you insist on using a color image then "
      "run it though RGBToHSV then ExtractComponents to get the V "
      "components. That's probably what you want anyhow.");
    return;
    }

  void* inPtr = inputArray->GetVoidPointer(0);
  double* outPtr = static_cast<double *>(
    output->GetScalarPointerForExtent(outExt));
  switch(inputArray->GetDataType())
    {
    vtkTemplateMacro(
      vtkImageGradientExecute(this, input, static_cast<VTK_TT*>(inPtr),
                              output, outPtr, outExt, threadId)
      );
    default:
      vtkErrorMacro("Execute: Unknown ScalarType " << input->GetScalarType());
      return;
    }
}
