RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkPolyData *input = vtkPolyData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));


  vtkDebugMacro(<<"Shrinking polygonal data");

  if (input == NULL || input->GetPoints() == NULL)
    {
    return 1;
    }


  void *inPtr = input->GetPoints()->GetVoidPointer(0);


  switch (input->GetPoints()->GetDataType())
    {
    vtkTemplateMacro(
      vtkShrinkPolyDataExecute(this,
                               (VTK_TT *)(inPtr), this->ShrinkFactor,
                               inInfo, outInfo));
    default:
      break;
    }

  return 1;
}
