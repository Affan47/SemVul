GetOutEdge(vtkIdType v, vtkIdType i)
{
  vtkIdType index = v;
  if (vtkDistributedGraphHelper *helper = this->GetDistributedGraphHelper())
    {
    int myRank = this->Information->Get(vtkDataObject::DATA_PIECE_NUMBER());
    if (myRank != helper->GetVertexOwner(v))
      {
      vtkErrorMacro("vtkGraph cannot retrieve the out edges for non-local vertex " << v);
      int* p = 0;
      *p = 17;
      return vtkOutEdgeType();
      }
    index = helper->GetVertexIndex(v);
    }

  if (i < this->GetOutDegree(v))
    {
    return this->Internals->Adjacency[index].OutEdges[i];
    }
  vtkErrorMacro("Out edge index out of bounds");
  return vtkOutEdgeType();
}
