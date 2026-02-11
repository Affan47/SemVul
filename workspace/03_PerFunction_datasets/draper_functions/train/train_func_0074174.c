PlaceWidget(double bds[6])
{
  int i;
  double bounds[6], origin[3];

  this->AdjustBounds(bds, bounds, origin);


  this->Box->SetOrigin(bounds[0],bounds[2],bounds[4]);
  this->Box->SetSpacing((bounds[1]-bounds[0]),(bounds[3]-bounds[2]),
                        (bounds[5]-bounds[4]));
  this->Outline->Update();

  this->LineSource->SetPoint1(this->Plane->GetOrigin());
  if ( this->NormalToYAxis )
    {
    this->Plane->SetNormal(0,1,0);
    this->LineSource->SetPoint2(0,1,0);
    }
  else if ( this->NormalToZAxis )
    {
    this->Plane->SetNormal(0,0,1);
    this->LineSource->SetPoint2(0,0,1);
    }
  else
    {
    this->Plane->SetNormal(1,0,0);
    this->LineSource->SetPoint2(1,0,0);
    }

  for (i=0; i<6; i++)
    {
    this->InitialBounds[i] = bounds[i];
    }

  this->InitialLength = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
                             (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
                             (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));

  this->ValidPick = 1;
  this->BuildRepresentation();
}
