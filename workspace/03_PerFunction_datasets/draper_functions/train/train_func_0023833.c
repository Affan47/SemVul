UpdateData(vtkDataObject* output)
{
  if(vtkDemandDrivenPipeline* ddp =
     vtkDemandDrivenPipeline::SafeDownCast(this->GetExecutive()))
    {
    if(output)
      {
      for(int i=0; i < this->NumberOfOutputs; ++i)
        {
        if(this->Outputs[i] == output)
          {
          ddp->UpdateData(i);
          }
        }
      }
    else
      {
      ddp->UpdateData(-1);
      }
    }
  else
    {
    vtkErrorMacro("Executive is not a vtkDemandDrivenPipeline.");
    }
}
