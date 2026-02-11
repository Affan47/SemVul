FillOutputPortInformation(
  int port, vtkInformation* info)
{

  if (port==0) {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData");
  }
  else if (port==1) {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData");
  }
  return 1;
}
