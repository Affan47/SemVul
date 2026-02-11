buildBasisMatrix (const OsiSolverInterface *si)
{ std::string solverName ;
  si->getStrParam(OsiSolverName,solverName) ;

  CoinPackedMatrix *basisMtx = new CoinPackedMatrix() ;
  const CoinPackedMatrix *mtx = si->getMatrixByCol() ;

  int m = si->getNumRows() ;
  int n = si->getNumCols() ;
  int *basicIndices = new int[m] ;
  si->getBasics(basicIndices) ;

  for (int i = 0 ; i < m ; i++)
  { int j = basicIndices[i] ;
    if (j < n)
    { if (OsiUnitTest::verbosity >= 2)
      { std::cout
	  << "  Retrieving column " << j << " for basis pos'n " << i << "."
	  << std::endl ; }
      CoinShallowPackedVector col = mtx->getVector(j) ;
      basisMtx->appendCol(col) ; }
    else
    { j -= n ;
      if (OsiUnitTest::verbosity >= 2)
      { std::cout
	  << "  Fabricating e<" << j << "> for basis pos'n " << i << "."
	  << std::endl ; }
      CoinPackedVector ei = CoinPackedVector(1,&j,1.0) ;
      basisMtx->appendCol(ei) ; } }

  return (basisMtx) ; }
