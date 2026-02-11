ThreadedRequestData (
  vtkInformation * vtkNotUsed( request ),
  vtkInformationVector** vtkNotUsed( inputVector ),
  vtkInformationVector * vtkNotUsed( outputVector ),
  vtkImageData ***inData,
  vtkImageData **outData,
  int outExt[6], int id)
{
  if (inData[0][0] == NULL)
    {
    vtkErrorMacro(<< "Input " << 0 << " must be specified.");
    return;
    }

  int numInputs = this->GetNumberOfInputConnections(0);
  int numWeights = this->Weights->GetNumberOfTuples();
  if( numWeights != numInputs )
    {
    vtkErrorMacro( << "Execute: There are " << numInputs << " vtkImageData provided"
      << " but only " << numWeights << " number of weights provided" );
    return;
    }

  switch (inData[0][0]->GetScalarType())
    {
    vtkTemplateMacro(
      vtkImageWeightedSumExecute(this , inData[0], numInputs,
        outData[0], outExt, id, static_cast<VTK_TT *>(0))
      );
    default:
      vtkErrorMacro(<< "Execute: Unknown ScalarType");
      return;
    }
}
