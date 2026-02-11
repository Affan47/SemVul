GetLastWeights( double * w )
{
  if ( this->LastCellId < 0 )
    {
    return 0;
    }

  int   numPts = this->GenCell->GetNumberOfPoints();
  for ( int i = 0; i < numPts; i ++ )
    {
    w[i] = this->Weights[i];
    }

  return 1;
}
