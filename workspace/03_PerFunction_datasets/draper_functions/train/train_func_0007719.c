getClusteredEvent( const double RN, int nSteps,
                Event& outState) {


  History *  selected = select(RN);


  selected->setScalesInHistory();


  if (nSteps > selected->nClusterings()) return false;


  outState = selected->clusteredState(nSteps-1);

  return true;

}
