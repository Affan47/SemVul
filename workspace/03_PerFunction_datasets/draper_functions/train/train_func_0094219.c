GetInDegree(vtkIdType v)
{
  vtkIdType index = v;

  if (vtkDistributedGraphHelper *helper = this->GetDistributedGraphHelper())
    {
    int myRank = this->Information->Get(vtkDataObject::DATA_PIECE_NUMBER());
    if (myRank != helper->GetVertexOwner(v))
      {
      vtkErrorMacro("vtkGraph cannot determine the in degree for a non-local vertex");
      return 0;
      }

    index = helper->GetVertexIndex(v);
    }

  return this->Internals->Adjacency[index].InEdges.size();
}
