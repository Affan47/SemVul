PlaceWidget(double bds[6])
{
  int i;
  double bounds[6], center[3];

  double placeFactor = this->PlaceFactor;
  this->PlaceFactor = 1.0;
  this->AdjustBounds(bds, bounds, center);
  this->PlaceFactor = placeFactor;

  for (i=0; i<6; i++)
    {
    this->InitialBounds[i] = bounds[i];
    }
  this->InitialLength = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
                             (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
                             (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));


  double p1[3], p2[3], r[3], o[3], t, placedP1[3], placedP2[3];
  this->LineSource->GetPoint1(p1);
  this->LineSource->GetPoint2(p2);


  r[0] = this->InitialLength * (p1[0] - p2[0]);
  r[1] = this->InitialLength * (p1[1] - p2[1]);
  r[2] = this->InitialLength * (p1[2] - p2[2]);
  o[0] = center[0] - r[0];
  o[1] = center[1] - r[1];
  o[2] = center[2] - r[2];
  vtkBox::IntersectBox(bounds,o,r,placedP1,t);
  this->SetPoint1WorldPosition(placedP1);

  r[0] = this->InitialLength * (p2[0] - p1[0]);
  r[1] = this->InitialLength * (p2[1] - p1[1]);
  r[2] = this->InitialLength * (p2[2] - p1[2]);
  o[0] = center[0] - r[0];
  o[1] = center[1] - r[1];
  o[2] = center[2] - r[2];
  vtkBox::IntersectBox(bounds,o,r,placedP2,t);
  this->SetPoint2WorldPosition(placedP2);


  this->LineHandleRepresentation->SetWorldPosition(center);


  this->Placed = 1;
  this->ValidPick = 1;
  this->BuildRepresentation();
}
