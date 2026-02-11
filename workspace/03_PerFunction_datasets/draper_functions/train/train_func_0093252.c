FillInputPortInformation(
  int port, vtkInformation* info)
{
  this->Superclass::FillInputPortInformation(port, info);
  if (port == 1)
    {


    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataObject");
    }
  return 1;
}
