FindGreater(vtkIdType nodeId,
                                                    vtkIdType startingNodeId,
                                                    vtkReebLabelTag label)
{
  if (!this->GetNode(nodeId)->IsFinalized)
    return 0;


  if (vtkReebGraphIsHigherThan(this, nodeId, startingNodeId, this->GetNode(nodeId), this->GetNode(startingNodeId)))
    return nodeId;


  for (vtkIdType A = this->GetNode(nodeId)->ArcUpId; A; A = this->GetArc(A)->ArcDwId0)
  {
    vtkReebArc* a = this->GetArc(A);
    vtkIdType M = this->GetArc(A)->NodeId1;
    vtkReebNode* m = this->GetNode(M);

    if (a->LabelId0 || !m->IsFinalized)
      {
      continue;
      }

    if ((M = FindGreater(M, startingNodeId, label)))
    {
      if (label)
        {
        SetLabel(A, label);
        }
      return M;
    }
  }

  return 0;
}
