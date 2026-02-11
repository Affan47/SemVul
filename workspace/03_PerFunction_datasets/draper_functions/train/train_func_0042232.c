FindAndTraverseFromSources
(vtkExecutive *exec, vtkExecutiveSet &visited)
{
  if (visited.find(exec) != visited.end())
    {
    return;
    }
  visited.insert(exec);
  bool isSource = true;
  for(int i = 0; i < exec->GetNumberOfInputPorts(); ++i)
    {
    int nic = exec->GetAlgorithm()->GetNumberOfInputConnections(i);
    vtkInformationVector* inVector = exec->GetInputInformation()[i];
    for(int j = 0; j < nic; ++j)
      {
      vtkInformation* inInfo = inVector->GetInformationObject(j);
      vtkExecutive* e;
      int producerPort;
      vtkExecutive::PRODUCER()->Get(inInfo, e, producerPort);
      if (e)
        {
        isSource = false;
        this->FindAndTraverseFromSources(e, visited);
        }
      }
    }
  if (isSource)
    {
    vtkExecutiveSet upstream;
    vtkExecutiveSet downVisited;
    this->TraverseDownToSink(exec, upstream, downVisited);
    }
}
