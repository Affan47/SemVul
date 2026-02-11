FillInputPortInformation(
  int portNumber, vtkInformation *info)
{
  if(!portNumber){
    info->Remove(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE());
    info->Append(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkReebGraph");
  }
  return 1;
}
