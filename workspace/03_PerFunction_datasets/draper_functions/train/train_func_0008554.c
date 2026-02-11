FastCompute
  ( vtkDataArray * vectors, double f[3] )
{
  int    pntIdx;
  int    numPts = this->GenCell->GetNumberOfPoints();
  double vector[3];
  f[0] = f[1] = f[2] = 0.0;

  for ( int i = 0; i < numPts; i ++ )
    {
    pntIdx = this->GenCell->PointIds->GetId( i );
    vectors->GetTuple( pntIdx, vector );
    f[0] += vector[0] * this->Weights[i];
    f[1] += vector[1] * this->Weights[i];
    f[2] += vector[2] * this->Weights[i];
    }
}
