ExecuteInformation
(vtkInformation* request,
 vtkInformationVector** inInfoVec,
 vtkInformationVector* outInfoVec)
{


  vtkInformation* inInfo = 0;
  if(this->GetNumberOfInputPorts() > 0)
    {
    inInfo = inInfoVec[0]->GetInformationObject(0);
    }
  for(int i=0; i < this->Algorithm->GetNumberOfOutputPorts(); ++i)
    {
    vtkInformation* outInfo = outInfoVec->GetInformationObject(i);
    if(vtkDataObject* outData = outInfo->Get(vtkDataObject::DATA_OBJECT()))
      {
      outData->CopyInformationToPipeline(request, inInfo);
      }
    }


  return this->CallAlgorithm(request, vtkExecutive::RequestDownstream,
                             inInfoVec, outInfoVec);
}
