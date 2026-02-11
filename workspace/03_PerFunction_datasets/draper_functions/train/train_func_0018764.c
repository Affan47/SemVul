extractRow (int i,
					const CoinPresolveMatrix *mtx) const
{
  const CoinBigIndex *rowStarts = mtx->getRowStarts() ;
  const int *colIndices = mtx->getColIndicesByRow() ;
  const double *coeffs = mtx->getElementsByRow() ;
  const int rowLen = mtx->hinrow_[i] ;
  const CoinBigIndex &ii = rowStarts[i] ;
  return (new CoinPackedVector(rowLen,&colIndices[ii],&coeffs[ii])) ;
}
