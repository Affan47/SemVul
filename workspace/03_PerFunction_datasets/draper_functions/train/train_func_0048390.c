execute()
{
  __variationalFormula->execute();
  __dirichletList->execute();
  __testFunctionList->execute();

  __unknownList = Information::instance().getUnknownList();

  std::vector<ReferenceCounting<BoundaryConditionSet> > listOfBCSet;
  listOfBCSet.resize(__testFunctionList->size());

  for (size_t i=0; i<listOfBCSet.size(); ++i) {
    listOfBCSet[i] = new BoundaryConditionSet();
  }

  for (VariationalDirichletListExpression::iterator
	 i = __dirichletList->begin();
       i != __dirichletList->end(); ++i) {
    size_t number = __unknownList->number((*i)->unknownName());
    BoundaryConditionSet& bcSet = (*listOfBCSet[number]);
    const BoundaryCondition& b = * (*i)->boundaryCondition();
    if (b.boundary()->type() == Boundary::list) {
      const Boundary* bc = b.boundary();
      const PDECondition* pde = b.condition();

      this->__splitBoundaryList(bcSet, pde, bc);
    } else {
      bcSet.addBoundaryCondition((*i)->boundaryCondition());
    }
  }


  std::vector<ConstReferenceCounting<BoundaryConditionSet> > listOfConstBCSet;
  listOfConstBCSet.resize(listOfBCSet.size());
  for (size_t i=0; i<listOfBCSet.size(); ++i) {
    listOfConstBCSet[i] = listOfBCSet[i];
  }

  __variationalProblem =  new VariationalProblem(listOfConstBCSet);

  __internalSetBilinear<AlgebraicPlus>(__variationalFormula->__bilinearPlus);
  __internalSetBilinear<AlgebraicMinus>(__variationalFormula->__bilinearMinus);

  __internalSetLinear<AlgebraicPlus>(__variationalFormula->__linearPlus);
  __internalSetLinear<AlgebraicMinus>(__variationalFormula->__linearMinus);

  __internalSetBilinearBC<AlgebraicPlus>(__variationalFormula->__bilinearBorderPlus);
  __internalSetBilinearBC<AlgebraicMinus>(__variationalFormula->__bilinearBorderMinus);

  __internalSetLinearBC<AlgebraicPlus>(__variationalFormula->__linearBorderPlus);
  __internalSetLinearBC<AlgebraicMinus>(__variationalFormula->__linearBorderMinus);
}
