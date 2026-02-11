AllocateOutputData(vtkDataObject *output,
                                                 int outputPort)
{

  vtkStructuredGrid *out = vtkStructuredGrid::SafeDownCast(output);
  if (out)
    {

    vtkStreamingDemandDrivenPipeline *sddp =
      vtkStreamingDemandDrivenPipeline::SafeDownCast(this->GetExecutive());
    int numInfoObj = sddp->GetNumberOfOutputPorts();
    if (sddp && outputPort<numInfoObj)
      {
      int extent[6];
      sddp->GetOutputInformation(outputPort)->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),extent);
      out->SetExtent(extent);
      }
    else
      {
      vtkWarningMacro( "Not enough output ports." );
      return;
      }
    this->AllocateScalars(out);
    }
  else
    {
    vtkImageData *out2 = vtkImageData::SafeDownCast(output);
    if (out2)
      {

      vtkStreamingDemandDrivenPipeline *sddp =
        vtkStreamingDemandDrivenPipeline::SafeDownCast(this->GetExecutive());
      int numInfoObj = sddp->GetNumberOfOutputPorts();
      if (sddp && outputPort<numInfoObj)
        {
        int extent[6];
        sddp->GetOutputInformation(outputPort)->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),extent);
        out2->SetExtent(extent);
        }
      else
        {
        vtkWarningMacro( "Not enough output ports." );
        return;
        }
      out2->SetNumberOfScalarComponents(3);
      out2->AllocateScalars();
      }
    }
}
