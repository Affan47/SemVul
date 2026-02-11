ComputePriority()
{
  vtkStreamingDemandDrivenPipeline *sddp =
    vtkStreamingDemandDrivenPipeline::SafeDownCast
      (this->GetExecutive());
  if (!sddp)
    {
    return 1.0;
    }
  return sddp->ComputePriority(0);
}
