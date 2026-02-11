SetProjectionPosition(double position)
{
  this->ProjectionPosition = position;
  if ( this->ProjectToPlane )
    {
    this->ProjectPointsToPlane();
    }
  this->BuildRepresentation();
}
