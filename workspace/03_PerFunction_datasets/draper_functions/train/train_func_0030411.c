GetOutEdges(vtkIdType v, vtkOutEdgeIterator *it)
{
  if (vtkDistributedGraphHelper *helper = this->GetDistributedGraphHelper())
    {
    int myRank = this->Information->Get(vtkDataObject::DATA_PIECE_NUMBER());
    if (myRank != helper->GetVertexOwner(v))
      {
      vtkErrorMacro("vtkGraph cannot retrieve the out edges for non-local vertex " << v);
      int* p = 0;
      *p = 17;
      return;
      }
    }

  if (it)
    {
    it->Initialize(this, v);
    }
}
