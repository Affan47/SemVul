getStartingConditions( const double RN, Event& outState ) {


  History *  selected = select(RN);


  selected->setScalesInHistory();


  outState = state;


  if (!selected->mother) {
    int nFinal = 0;
    for(int i=0; i < int(outState.size()); ++i)
      if (outState[i].isFinal()) nFinal++;
    if (nFinal <=2)
      outState.scale(mergingHooksPtr->muF());


      if (mergingHooksPtr->getNumberOfClusteringSteps(state) == 0) {
        infoPtr->zNowISR(0.5);
        infoPtr->pT2NowISR(pow(state[0].e(),2));
        infoPtr->hasHistory(true);

      } else {
        infoPtr->zNowISR(selected->zISR());
        infoPtr->pT2NowISR(pow(selected->pTISR(),2));
        infoPtr->hasHistory(true);
      }

  } else {


    infoPtr->zNowISR(selected->zISR());
    infoPtr->pT2NowISR(pow(selected->pTISR(),2));
    infoPtr->hasHistory(true);

  }

}
