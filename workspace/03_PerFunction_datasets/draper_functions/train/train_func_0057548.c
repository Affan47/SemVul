GetParametricDistance(double pcoords[3])
{
  int i;
  double pDist, pDistMax=0.0;

  for (i=0; i<3; i++)
    {
    if ( pcoords[i] < 0.0 )
      {
      pDist = -pcoords[i];
      }
    else if ( pcoords[i] > 1.0 )
      {
      pDist = pcoords[i] - 1.0;
      }
    else
      {
      pDist = 0.0;
      }
    if ( pDist > pDistMax )
      {
      pDistMax = pDist;
      }
    }
  return pDistMax;
}
