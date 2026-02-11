PlaceWidget(double corners[8][3])
{


  double center[3] = {0.0, 0.0, 0.0}, newCorners[8][3];
  for (int j = 0; j < 3; j++)
    {
    for (int i = 0; i < 8; center[j] += corners[i][j], i++)
      {
      ;
      }
    center[j] /= 8.0;

    for (int i = 0; i < 8; i++)
      {
      newCorners[i][j] = center[j] +
        this->PlaceFactor*(corners[i][j]-center[j]);
      }
    }

  for (int i = 0; i < 8; i++)
    {
    this->Points->SetPoint(i, newCorners[i]);
    }
  this->AbsoluteMinimumThickness =
    this->HexPolyData->GetLength()*this->MinimumThickness;

  this->ChairPointPlacer->SetMinimumDistance( 0.5 * this->AbsoluteMinimumThickness );


  for (int i = 8; i < 16; i++)
    {
    this->Points->SetPoint(i, newCorners[0]);
    }

  this->PositionHandles();
}
