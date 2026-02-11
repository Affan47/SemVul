Point3WidgetInteraction(double e[2])
{
  double p1[3], p2[3], p3[3], p4[3];
  double slope1[3], slope2[3];


  this->GetPoint1WorldPosition(p1);
  this->GetPoint2WorldPosition(p2);
  slope1[0] = p2[0] - p1[0];
  slope1[1] = p2[1] - p1[1];
  slope2[0] = -slope1[1];
  slope2[1] =  slope1[0];
  slope2[2] = 0.0;
  vtkMath::Normalize(slope2);


  double pw[4], t, closest[3];
  if ( this->Renderer )
    {
    this->Renderer->SetDisplayPoint(e[0],e[1],0.0);
    this->Renderer->DisplayToWorld();
    this->Renderer->GetWorldPoint(pw);
    }
  double dist = sqrt(vtkLine::DistanceToLine(pw,p1,p2,t,closest));


  p3[0] = closest[0] + dist*slope2[0];
  p3[1] = closest[1] + dist*slope2[1];
  p3[2] = pw[2];
  this->SetPoint3WorldPosition(p3);

  p4[0] = closest[0] - dist*slope2[0];
  p4[1] = closest[1] - dist*slope2[1];
  p4[2] = pw[2];
  this->SetPoint4WorldPosition(p4);
}
