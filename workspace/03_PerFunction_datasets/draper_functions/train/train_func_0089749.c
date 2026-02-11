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

  if (!this->SampleArrayName)
    {
    vtkErrorMacro(<<"DistanceToSpheresArrayName not set.");
    return 1;
    }

  if (!this->ImplicitFunction)
    {
    vtkErrorMacro(<<"ImplicitFunction not set.");
    return 1;
    }

  int numberOfInputPoints = input->GetNumberOfPoints();

  output->DeepCopy(input);


  vtkDataArray* sampleArray =  output->GetPointData()->GetArray(this->SampleArrayName);

  bool createArray = !sampleArray;

  if (createArray)
    {
    sampleArray = vtkDoubleArray::New();
    sampleArray->SetName(this->SampleArrayName);
    sampleArray->SetNumberOfComponents(1);
    sampleArray->SetNumberOfTuples(numberOfInputPoints);
    sampleArray->FillComponent(0, 0);
    output->GetPointData()->AddArray(sampleArray);
    }


  double point[3];
  for (int i=0; i<numberOfInputPoints; i++)
    {
    input->GetPoint(i,point);
    sampleArray->SetComponent(i,0,this->ImplicitFunction->EvaluateFunction(point));
    }

  if (createArray) sampleArray->Delete();

  return 1;
}
