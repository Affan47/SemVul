readMps(const char * filename,
    const char * extension)
{
  CoinMpsIO m;

  int logLvl = handler_->logLevel() ;
  if (logLvl > 1)
  { m.messageHandler()->setLogLevel(handler_->logLevel()) ; }
  else
  { m.messageHandler()->setLogLevel(0) ; }
  m.setInfinity(getInfinity());

  int numberErrors = m.readMps(filename,extension);
  handler_->message(COIN_SOLVER_MPS,messages_)
    <<m.getProblemName()<< numberErrors <<CoinMessageEol;
  if (!numberErrors) {


    setDblParam(OsiObjOffset,m.objectiveOffset());


    setStrParam(OsiProbName,m.getProblemName());


    loadProblem(*m.getMatrixByCol(),m.getColLower(),m.getColUpper(),
		m.getObjCoefficients(),m.getRowSense(),m.getRightHandSide(),
		m.getRowRange());
    setRowColNames(m) ;
    const char * integer = m.integerColumns();
    if (integer) {
      int i,n=0;
      int nCols=m.getNumCols();
      int * index = new int [nCols];
      for (i=0;i<nCols;i++) {
	if (integer[i]) {
	  index[n++]=i;
	}
      }
      setInteger(index,n);
      delete [] index;
    }
  }
  return numberErrors;
}
