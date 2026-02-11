ExecuteDataEnd(vtkInformation* request,
                 vtkInformationVector** inInfoVec,
                 vtkInformationVector* outInfoVec)
{


  if(request->Get(CONTINUE_EXECUTING()))
    {
    this->ContinueExecuting = 1;
    this->Update(request->Get(FROM_OUTPUT_PORT()));
    }
  else
    {
    this->ContinueExecuting = 0;
    this->Superclass::ExecuteDataEnd(request,inInfoVec,outInfoVec);
    }
}
