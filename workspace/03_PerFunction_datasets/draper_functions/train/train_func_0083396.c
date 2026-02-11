DeepCopy(vtkDataObject* src)
{
  vtkSelection *input = vtkSelection::SafeDownCast(src);
  if (!input)
    {
    return;
    }
  this->Initialize();
  this->Superclass::DeepCopy(src);
  unsigned int numNodes = input->GetNumberOfNodes();
  for (unsigned int i=0; i<numNodes; i++)
    {
    vtkSmartPointer<vtkSelectionNode> newNode =
      vtkSmartPointer<vtkSelectionNode>::New();
    newNode->DeepCopy(input->GetNode(i));
    this->AddNode(newNode);
    }
  this->Modified();
}
