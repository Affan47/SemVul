weightTREE(PartonLevel* trial, AlphaStrong * asFSR,
                  AlphaStrong * asISR, double RN) {

  if ( mergingHooksPtr->canCutOnRecState() && !foundAllowedPath ) {
    string message="Warning in History::weightTREE: No allowed history";
    message+=" found. Using disallowed history.";
    infoPtr->errorMsg(message);
  }
  if ( mergingHooksPtr->orderHistories() && !foundOrderedPath ) {
    string message="Warning in History::weightTREE: No ordered history";
    message+=" found. Using unordered history.";
    infoPtr->errorMsg(message);
  }
  if ( mergingHooksPtr->canCutOnRecState()
    && mergingHooksPtr->orderHistories()
    && !foundAllowedPath && !foundOrderedPath ) {
    string message="Warning in History::weightTREE: No allowed or ordered";
    message+=" history found.";
    infoPtr->errorMsg(message);
  }


  double asME     = infoPtr->alphaS();
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  History *  selected = select(RN);

  selected->setScalesInHistory();

  double asWeight  = 1.;
  double pdfWeight = 1.;


  double wt    = selected->weightTree( trial, asME, maxScale,
                   selected->clusterIn.pT(), asFSR, asISR, asWeight,
                   pdfWeight );

  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = selected->weightTreeEmissions( trial, -1, njetsMaxMPI,
                   maxScale );


  bool resetScales = mergingHooksPtr->resetHardQRen();


  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>jj") == 0) {

    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*asFSR).alphaS(newQ2Ren) / asME;
    asWeight *= pow2(runningCoupling);
  }


  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>aj") == 0) {

    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling =
      (*asISR).alphaS( newQ2Ren + pow(mergingHooksPtr->pT0ISR(),2) ) / asME;
    asWeight *= runningCoupling;
  }


  return (wt*asWeight*pdfWeight*mpiwt);

}
