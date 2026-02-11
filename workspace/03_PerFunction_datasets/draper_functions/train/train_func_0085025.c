GetBucketNeighbors(int ijk[3], int ndivs, int level)
{
  int i, j, k, min, max, minLevel[3], maxLevel[3];
  int nei[3];
  int leafStart;
  int numberOfBucketsPerPlane;

  this->BuildLocatorIfNeeded();

  numberOfBucketsPerPlane = this->NumberOfDivisions*this->NumberOfDivisions;
  leafStart = this->NumberOfOctants
    - numberOfBucketsPerPlane*this->NumberOfDivisions;


  this->Buckets->Reset();


  if ( level == 0 )
    {
    if (this->Tree[leafStart + ijk[0] + ijk[1]*this->NumberOfDivisions
      + ijk[2]*numberOfBucketsPerPlane])
      {
      this->Buckets->InsertNextPoint(ijk);
      }
    return;
    }


  for ( i=0; i<3; i++ )
    {
    min = ijk[i] - level;
    max = ijk[i] + level;
    minLevel[i] = ( min > 0 ? min : 0);
    maxLevel[i] = ( max < (ndivs-1) ? max : (ndivs-1));
    }

  for ( k= minLevel[2]; k <= maxLevel[2]; k++ )
    {
    for ( j= minLevel[1]; j <= maxLevel[1]; j++ )
      {
      for ( i= minLevel[0]; i <= maxLevel[0]; i++ )
        {
        if (i == (ijk[0] + level) || i == (ijk[0] - level) ||
          j == (ijk[1] + level) || j == (ijk[1] - level) ||
          k == (ijk[2] + level) || k == (ijk[2] - level) )
          {
          if (this->Tree[leafStart + i + j*this->NumberOfDivisions
            + k*numberOfBucketsPerPlane])
            {
            nei[0]=i; nei[1]=j; nei[2]=k;
            this->Buckets->InsertNextPoint(nei);
            }
          }
        }
      }
    }

  return;
}
