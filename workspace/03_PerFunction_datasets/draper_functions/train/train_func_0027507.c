ComputeSplits(unsigned int dim,
                unsigned int requestedNumber,
                const IndexValueType itkNotUsed(regionIndex)[],
                const SizeValueType regionSize[],
                unsigned int splits[])
{

  std::vector<double> splitRegionSize(dim);
  unsigned int numberOfPieces = 1;


  for ( unsigned int i = 0; i < dim; ++i )
    {
    splits[i] = 1;
    splitRegionSize[i] = regionSize[i];
    }

  while ( true )
    {

    unsigned int maxSplitDim = 0;
    for ( unsigned int i = 1; i < dim; ++i )
      {
      if ( splitRegionSize[maxSplitDim] < splitRegionSize[i] )
        {
        maxSplitDim = i;
        }
      }


    unsigned int additionalNumPieces = 1;
    for ( unsigned int i = 0; i < dim; ++i )
      {
      if ( i != maxSplitDim )
        {
        additionalNumPieces *= splits[i];
        }
      }


    if ( numberOfPieces + additionalNumPieces > requestedNumber
         || splits[maxSplitDim] == regionSize[maxSplitDim] )
      {
      return numberOfPieces;
      }


    numberOfPieces += additionalNumPieces;
    ++splits[maxSplitDim];
    splitRegionSize[maxSplitDim] = regionSize[maxSplitDim] / double(splits[maxSplitDim]);
    }
}
