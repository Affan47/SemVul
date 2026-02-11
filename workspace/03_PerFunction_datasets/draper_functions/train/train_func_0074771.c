RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation *selInfo = inputVector[1]->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkDataSet *input = vtkDataSet::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  if ( ! input )
    {
    vtkErrorMacro(<<"No input specified");
    return 0;
    }

  if ( ! selInfo )
    {

    return 1;
    }

  vtkSelection *sel = vtkSelection::SafeDownCast(
    selInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkSelectionNode *node = 0;
  if (sel->GetNumberOfNodes() == 1)
    {
    node = sel->GetNode(0);
    }
  if (!node)
    {
    vtkErrorMacro("Selection must have a single node.");
    return 0;
    }
  if (node->GetContentType() != vtkSelectionNode::LOCATIONS)
    {
    vtkErrorMacro("Incompatible CONTENT_TYPE.");
    return 0;
    }

  vtkDataSet *output = vtkDataSet::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkDebugMacro(<< "Extracting from dataset");

  int fieldType = vtkSelectionNode::CELL;
  if (node->GetProperties()->Has(vtkSelectionNode::FIELD_TYPE()))
    {
    fieldType = node->GetProperties()->Get(vtkSelectionNode::FIELD_TYPE());
    }
  switch (fieldType)
    {
    case vtkSelectionNode::CELL:
      return this->ExtractCells(node, input, output);
    case vtkSelectionNode::POINT:
      return this->ExtractPoints(node, input, output);
    }
  return 1;
}
