addME(Energy maxEnergy, tSubHdlPtr sub, tPExtrPtr extractor, tCutsPtr cuts,
      tCascHdlPtr ckkw, tMEPtr me, const PBPair & pBins) {

  typedef MEBase::DiagramVector DiagramVector;
  typedef map<string,DiagramVector> DiagramMap;
  cPDPair pin(pBins.first->parton(), pBins.second->parton());
  DiagramVector diag = me->diagrams();
  DiagramMap tdiag;
  DiagramMap tmdiag;
  for ( int i = 0, N = diag.size(); i < N; ++i ) {
    if ( diag[i]->partons()[0] == pin.first &&
         diag[i]->partons()[1] == pin.second )
      tdiag[diag[i]->getTag()].push_back(diag[i]);
    if ( diag[i]->partons()[0] == pin.second &&
         diag[i]->partons()[1] == pin.first )
      tmdiag[diag[i]->getTag()].push_back(diag[i]);
  }

  bool mirror = false;
  if ( ( mirror = tdiag.empty() ) ) tdiag = tmdiag;
  for ( DiagramMap::iterator dit = tdiag.begin(); dit != tdiag.end(); ++dit ) {


    StdXCombPtr xcomb =
      new_ptr(StandardXComb(maxEnergy, incoming(), eventHandler(),
			    sub, extractor, ckkw, pBins, cuts, me, dit->second, mirror));

    if ( xcomb->checkInit() ) xCombs().push_back(xcomb);

    else generator()->logWarning(
      InitError() << "The matrix element '"
      << xcomb->matrixElement()->name() << "' cannot generate the diagram '"
      << dit->first << "' when used together with the parton extractor '"
      << xcomb->pExtractor()->name()
      << "'. The corresponding diagram is switched off." << Exception::warning);
  }
}
