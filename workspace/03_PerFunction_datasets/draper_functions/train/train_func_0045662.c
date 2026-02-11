ComputeInputUpdateExtents(
  vtkDataObject *output)
{
  vtkDataObject *input = this->GetInput();

  if (input == NULL)
    {
    return;
    }

  this->vtkPolyDataSource::ComputeInputUpdateExtents(output);
  input->RequestExactExtentOn();
}
