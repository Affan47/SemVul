RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkGraph *input = vtkGraph::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  if (!this->DistanceToCamera->GetRenderer())
    {
    vtkErrorMacro("Need renderer set before updating the filter.");
    return 0;
    }

  vtkSmartPointer<vtkGraph> inputCopy;
  if (vtkDirectedGraph::SafeDownCast(input))
    {
    inputCopy.TakeReference(vtkDirectedGraph::New());
    }
  else
    {
    inputCopy.TakeReference(vtkUndirectedGraph::New());
    }
  inputCopy->ShallowCopy(input);

  this->DistanceToCamera->SetScreenSize(this->ScreenSize);
  this->GlyphSource->SetFilled(this->Filled);

  this->GraphToPoints->SetInput(inputCopy);
  vtkAbstractArray* arr = this->GetInputArrayToProcess(0, inputVector);
  if (arr)
    {
    this->DistanceToCamera->SetInputArrayToProcess(
      0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arr->GetName());
    }
  this->DistanceToCamera->SetInputConnection(
    this->GraphToPoints->GetOutputPort());
  this->Glyph->SetInputConnection(
    0, this->DistanceToCamera->GetOutputPort());
  if (this->GlyphType == SPHERE)
    {
    this->Glyph->SetInputConnection(
      1, this->Sphere->GetOutputPort());
    }
  else
    {
    this->Glyph->SetInputConnection(
      1, this->GlyphSource->GetOutputPort());
    this->GlyphSource->SetGlyphType(this->GlyphType);
    }
  this->Glyph->Update();

  output->ShallowCopy(this->Glyph->GetOutput());

  return 1;
}
