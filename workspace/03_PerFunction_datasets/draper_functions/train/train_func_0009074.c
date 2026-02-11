RequestDataObject(vtkInformation *request,
                                          vtkInformationVector **inputVector,
                                          vtkInformationVector *outputVector)
{
  vtkImageData *inImage = vtkImageData::GetData(inputVector[0]);
  vtkRectilinearGrid *inRect = vtkRectilinearGrid::GetData(inputVector[0]);

  if (inImage || inRect)
    {
    vtkStructuredGrid *output = vtkStructuredGrid::GetData(outputVector);
    if (!output)
      {
      vtkNew<vtkStructuredGrid> newOutput;
      newOutput->SetPipelineInformation(outputVector->GetInformationObject(0));
      }
    return 1;
    }
  else
    {
    return this->Superclass::RequestDataObject(request,
                                               inputVector,
                                               outputVector);
    }
}
