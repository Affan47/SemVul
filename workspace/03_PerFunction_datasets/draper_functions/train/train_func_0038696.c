RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkPolyData *input = vtkPolyData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  if (!this->AbscissasArrayName)
    {
    vtkErrorMacro(<<"AbscissasArrayName not specified");
    return 1;
    }

  if (!this->ParallelTransportNormalsArrayName)
    {
    vtkErrorMacro(<<"ParallelTransportNormalsArrayName not specified");
    return 1;
    }

  output->DeepCopy(input);

  vtkDoubleArray* abscissasArray = vtkDoubleArray::New();
  abscissasArray->SetNumberOfComponents(1);
  abscissasArray->SetName(this->AbscissasArrayName);

  this->ComputeAbscissas(input,abscissasArray);
  output->GetPointData()->AddArray(abscissasArray);

  vtkDoubleArray* parallelTransportNormalsArray = vtkDoubleArray::New();
  parallelTransportNormalsArray->SetNumberOfComponents(3);
  parallelTransportNormalsArray->SetName(this->ParallelTransportNormalsArrayName);

  this->ComputeParallelTransportNormals(input,parallelTransportNormalsArray);
  output->GetPointData()->AddArray(parallelTransportNormalsArray);

  abscissasArray->Delete();
  parallelTransportNormalsArray->Delete();

  return 1;
}
