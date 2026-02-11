refreshSolver(OsiSolverInterface * solver)
{
  int numberColumns=solver->getNumCols();
  const double * colUpper = solver->getColUpper();
  const double * colLower = solver->getColLower();
  canDoGlobalCuts_ = true;
  if (originalSolver_) {
    delete originalSolver_;
    originalSolver_ = solver->clone();
  }
  for (int i=0;i<numberColumns;i++) {
    if (solver->isInteger(i)) {
      if (colUpper[i]>colLower[i]+1.0) {
	canDoGlobalCuts_ = false;
	break;
      }
    }
  }
}
