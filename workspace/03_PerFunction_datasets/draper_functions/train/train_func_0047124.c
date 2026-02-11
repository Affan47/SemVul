getBInvARow(int row, CoinIndexedVector * columnArray0, CoinIndexedVector * slack,
				   bool keepScaled) const
{
#ifndef NDEBUG
  int nx = modelPtr_->numberRows();
  if (row<0||row>=nx) {
    indexError(row,"getBInvARow");
  }
#endif

  CoinIndexedVector * rowArray0 = modelPtr_->rowArray(0);
  CoinIndexedVector * rowArray1 = slack ? slack : modelPtr_->rowArray(1);
  CoinIndexedVector * columnArray1 = modelPtr_->columnArray(1);
  rowArray0->clear();
  rowArray1->clear();
  columnArray0->clear();
  columnArray1->clear();

  int numberColumns = modelPtr_->numberColumns();


  const int * pivotVariable = modelPtr_->pivotVariable();
  const double * rowScale = modelPtr_->rowScale();
  const double * columnScale = modelPtr_->columnScale();
  int pivot = pivotVariable[row];
  double value;

  if (!rowScale) {
    if (pivot<numberColumns)
      value = 1.0;
    else
      value = -1.0;
  } else {
    if (pivot<numberColumns)
      value = columnScale[pivot];
    else
      value = -1.0/rowScale[pivot-numberColumns];
  }
  rowArray1->insert(row,value);
  modelPtr_->factorization()->updateColumnTranspose(rowArray0,rowArray1);

  modelPtr_->clpMatrix()->transposeTimes(modelPtr_,1.0,
                                         rowArray1,columnArray1,columnArray0);
  int n;
  const int * which;
  double * array;

  if (rowScale&&!keepScaled) {
    int j;

    n = columnArray0->getNumElements();
    which = columnArray0->getIndices();
    array = columnArray0->denseVector();
    for (j=0; j < n; j++) {
      int k=which[j];
      array[k] /= columnScale[k];
    }
    if (slack) {
      n = slack->getNumElements();
      which = slack->getIndices();
      array = slack->denseVector();
      for(j=0; j < n; j++) {
	int k=which[j];
	array[k] *= rowScale[k];
      }
    }
  }
  if (!slack)
    rowArray1->clear();
}
