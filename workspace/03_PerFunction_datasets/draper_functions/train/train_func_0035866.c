GetEdge(int edgeId)
{

  if ( ! this->EdgesGenerated )
    {
    this->GenerateEdges();
    }


  vtkIdType numEdges = this->Edges->GetNumberOfTuples();

  if ( edgeId < 0 || edgeId >= numEdges )
    {
    return NULL;
    }


  vtkIdType edge[2];
  this->Edges->GetTupleValue(edgeId,edge);


  for (int i=0; i<2; i++)
    {
    this->Line->PointIds->SetId(i,this->PointIds->GetId(edge[i]));
    this->Line->Points->SetPoint(i,this->Points->GetPoint(edge[i]));
    }

  return this->Line;
}
