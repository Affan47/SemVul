CallAlgorithm(vtkInformation* request, int direction,
                                vtkInformationVector** inInfo,
                                vtkInformationVector* outInfo)
{

  this->CopyDefaultInformation(request, direction, inInfo, outInfo);


  this->InAlgorithm = 1;
  int result = this->Algorithm->ProcessRequest(request, inInfo, outInfo);
  this->InAlgorithm = 0;


  if(!result)
    {
    vtkErrorMacro("Algorithm " << this->Algorithm->GetClassName()
                  << "(" << this->Algorithm
                  << ") returned failure for request: "
                  << *request);
    }

  return result;
}
