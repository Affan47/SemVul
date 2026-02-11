generateCuts(const OsiSolverInterface &si, OsiCuts & cs,
				const CglTreeInfo info)
{
  solver = const_cast<OsiSolverInterface *>(&si);
  if(solver == NULL) {
    printf("### WARNING: CglRedSplit2::generateCuts(): no solver available.\n");
    return;
  }

  if(!solver->optimalBasisIsAvailable()) {
    printf("### WARNING: CglRedSplit2::generateCuts(): no optimal basis available.\n");
    return;
  }


  card_intBasicVar = 0;
  card_intBasicVar_frac = 0;
  card_intNonBasicVar = 0;
  card_contNonBasicVar = 0;
  card_nonBasicAtUpper = 0;
  card_nonBasicAtLower = 0;
  numRedRows = 0;
  startTime = CoinCpuTime();


  ncol = solver->getNumCols();
  nrow = solver->getNumRows();
  colLower = solver->getColLower();
  colUpper = solver->getColUpper();
  rowLower = solver->getRowLower();
  rowUpper = solver->getRowUpper();
  rowRhs = solver->getRightHandSide();
  reducedCost = solver->getReducedCost();
  rowPrice = solver->getRowPrice();
  objective = solver->getObjCoefficients();

  xlp = solver->getColSolution();
  rowActivity = solver->getRowActivity();
  byRow = solver->getMatrixByRow();

  solver->enableFactorization();
  generateCuts(&cs, param.getMaxNumCuts());
  solver->disableFactorization();
}
