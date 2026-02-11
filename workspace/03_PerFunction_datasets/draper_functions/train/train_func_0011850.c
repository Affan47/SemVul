GetEdge(int edgeId)
{
  edgeId = (edgeId < 0 ? 0 : (edgeId > 5 ? 5 : edgeId ));


  this->Edge->PointIds->SetId(0,this->PointIds->GetId(TetraEdges[edgeId][0]));
  this->Edge->PointIds->SetId(1,this->PointIds->GetId(TetraEdges[edgeId][1]));
  this->Edge->PointIds->SetId(2,this->PointIds->GetId(TetraEdges[edgeId][2]));


  this->Edge->Points->SetPoint(0,this->Points->GetPoint(TetraEdges[edgeId][0]));
  this->Edge->Points->SetPoint(1,this->Points->GetPoint(TetraEdges[edgeId][1]));
  this->Edge->Points->SetPoint(2,this->Points->GetPoint(TetraEdges[edgeId][2]));

  return this->Edge;
}
