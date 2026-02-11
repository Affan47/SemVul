bestPivot(bool justColumns)
{


  double acceptablePivot = 1.0e-9;
  if (numberIterations_ > 100)
    acceptablePivot = 1.0e-8;
  if (factorization_->pivots() > 10 ||
      (factorization_->pivots() && sumDualInfeasibilities_))
    acceptablePivot = 1.0e-5;
  else if (factorization_->pivots() > 5)
    acceptablePivot = 1.0e-6;
  else if (factorization_->pivots())
    acceptablePivot = 1.0e-8;
  double bestPossiblePivot = 1.0;


  double direction = directionOut_;
#ifndef COIN_FAC_NEW
  rowArray_[0]->createPacked(1, &pivotRow_, &direction);
#else
  rowArray_[0]->createOneUnpackedElement(pivotRow_, direction);
#endif
  factorization_->updateColumnTranspose(rowArray_[1], rowArray_[0]);

  matrix_->transposeTimes(this, -1.0,
			  rowArray_[0], rowArray_[3], columnArray_[0]);
  sequenceIn_=-1;
  if (justColumns)
    rowArray_[0]->clear();

  bestPossiblePivot =
    reinterpret_cast<ClpSimplexDual *>
    ( this)->dualColumn(rowArray_[0],
			columnArray_[0], columnArray_[1],
			rowArray_[3], acceptablePivot, NULL);
  return bestPossiblePivot;
}
