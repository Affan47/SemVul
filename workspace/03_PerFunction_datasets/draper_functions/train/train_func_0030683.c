RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkPolyData *input = vtkPolyData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData *output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  this->TotalMarkedPoints = 0;

  vtkPolyData* model = vtkPolyData::New();
  model->DeepCopy(input);

  vtkIdTypeArray* marksArray = vtkIdTypeArray::New();
  marksArray->SetName(this->MarksArrayName);
  marksArray->SetNumberOfTuples(model->GetNumberOfPoints());
  model->GetPointData()->AddArray(marksArray);

  vtkPolyData* modelBoundary = vtkPolyData::New();
  this->BoundaryExtractor(model,modelBoundary);

  vtkPolyData* network = vtkPolyData::New();

  if (modelBoundary->GetNumberOfPoints() > 0)
    {
    this->MarkModelRealBoundary(model,modelBoundary);

    model->BuildCells();
    model->BuildLinks();

    vtkPolyDataCollection* globalProfiles = vtkPolyDataCollection::New();
    this->BoundarySeparator(modelBoundary,globalProfiles);

    this->GlobalIteration(model,globalProfiles,network,this->AdvancementRatio);
    globalProfiles->Delete();
    }

  marksArray->Delete();
  modelBoundary->Delete();

  double progress = 1.0;
  this->InvokeEvent(vtkCommand::ProgressEvent,&progress);

  output->DeepCopy(network);

  if (this->GraphLayout)
    {
    this->GraphLayout->Delete();
    this->GraphLayout = NULL;
    }

  this->GraphLayout = vtkPolyData::New();
  this->Graph(network,this->GraphLayout);

  network->Delete();

  return 1;
}
