operator=(const OsiSolverResult& rhs)
{
  if (this != &rhs) {
    delete [] primalSolution_;
    delete [] dualSolution_;
    objectiveValue_ = rhs.objectiveValue_;
    basis_ = rhs.basis_;
    fixed_ = rhs.fixed_;
    int numberRows = basis_.getNumArtificial();
    int numberColumns = basis_.getNumStructural();
    if (numberColumns) {
      primalSolution_ = CoinCopyOfArray(rhs.primalSolution_,numberColumns);
      dualSolution_ = CoinCopyOfArray(rhs.dualSolution_,numberRows);
    } else {
      primalSolution_=NULL;
      dualSolution_=NULL;
    }
  }
  return *this;
}
