makeGlobalCut(const OsiColCut * cut)
{
  const double * lower;
  const double * upper;
  if (topOfTree_) {
    lower = topOfTree_->lower();
    upper = topOfTree_->upper();
  } else {
    lower = solver_->getColLower();
    upper = solver_->getColUpper();
  }
  int nLower=cut->lbs().getNumElements();
  const int * indexLower=cut->lbs().getIndices();
  const double * boundLower=cut->lbs().getElements();
  for (int i=0;i<nLower;i++) {
    int iColumn=indexLower[i];
    double newValue=CoinMax(lower[iColumn],boundLower[iColumn]);
    if (topOfTree_)
      topOfTree_->setColLower(iColumn,newValue);
    else
      solver_->setColLower(iColumn,newValue);
  }
  int nUpper=cut->ubs().getNumElements();
  const int * indexUpper=cut->ubs().getIndices();
  const double * boundUpper=cut->ubs().getElements();
  for (int i=0;i<nUpper;i++) {
    int iColumn=indexUpper[i];
    double newValue=CoinMin(upper[iColumn],boundUpper[iColumn]);
    if (topOfTree_)
      topOfTree_->setColUpper(iColumn,newValue);
    else
      solver_->setColUpper(iColumn,newValue);
  }
}
