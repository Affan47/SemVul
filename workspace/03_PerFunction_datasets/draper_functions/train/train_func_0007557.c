updateColumnTransposeRDensish
( CoinIndexedVector * regionSparse ) const
{
  double * COIN_RESTRICT region = regionSparse->denseVector (  );

#ifdef COIN_DEBUG
  regionSparse->checkClean();
#endif
  int last = numberRowsExtra_-1;


  const int *indexRow = indexRowR_;
  const CoinFactorizationDouble *element = elementR_;
  const CoinBigIndex * startColumn = startColumnR_.array()-numberRows_;

  const int * permute = permute_.array();

  for (int i = last ; i >= numberRows_; i-- ) {
    int putRow = permute[i];
    CoinFactorizationDouble pivotValue = region[i];

    region[i] = 0.0;
    if ( pivotValue ) {
      for (CoinBigIndex j = startColumn[i]; j < startColumn[i+1]; j++ ) {
	CoinFactorizationDouble value = element[j];
	int iRow = indexRow[j];
	region[iRow] -= value * pivotValue;
      }
      region[putRow] = pivotValue;


    }
  }
}
