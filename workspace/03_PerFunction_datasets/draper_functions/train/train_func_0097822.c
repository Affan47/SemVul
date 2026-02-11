fillEventRecord(StepPtr step, bool firstInteraction, bool) {

  PPtr inSubPro = subProcess()->incoming().first;
  PPtr inParticle;
  if ( !(inSubPro->parents().empty()) )
    inParticle = inSubPro->parents()[0];
  else
    inParticle = inSubPro;
  PPtr inParton = theOriginals[inSubPro];
  theOriginals.erase(inSubPro);
  updateColour(incoming().first);
  if ( inParticle != inSubPro )
    inParticle->abandonChild(inSubPro);
  inParton->addChild(inSubPro);
  if ( inParticle != inSubPro )
    inParticle->addChild(incoming().first);
  theIntermediates.push_back(inSubPro);
  theIntermediates.push_back(inParton);

  inSubPro = subProcess()->incoming().second;
  if ( !(inSubPro->parents().empty()) )
    inParticle = inSubPro->parents()[0];
  else
    inParticle = inSubPro;
  inParton = theOriginals[inSubPro];
  theOriginals.erase(inSubPro);
  updateColour(incoming().second);
  if ( inParticle != inSubPro )
    inParticle->abandonChild(inSubPro);
  inParton->addChild(inSubPro);
  if ( inParticle != inSubPro )
    inParticle->addChild(incoming().second);
  theIntermediates.push_back(inSubPro);
  theIntermediates.push_back(inParton);

  while ( !theOriginals.empty() ) {
    PPtr outSubPro = theOriginals.begin()->first;
    PPtr outParton = theOriginals.begin()->second;
    theOriginals.erase(theOriginals.begin());
    updateColour(outParton);
    outSubPro->addChild(outParton);
    theIntermediates.push_back(outSubPro);
  }

  step->addIntermediates(theIntermediates.begin(),theIntermediates.end());

  for (PList::const_iterator p = theOutgoing.begin();
       p != theOutgoing.end(); ++p)
    step->addDecayProduct(*p);

  for (PList::const_iterator p = theHard.begin();
       p != theHard.end(); ++p)
    step->addDecayProduct(*p);

  if ( firstInteraction &&
       (theIncoming.first->coloured() ||
	theIncoming.second->coloured() ) ) {
      ShowerHandler::currentHandler()->lastExtractor()->newRemnants(theSubProcess->incoming(),theIncoming,step);
  }

  step->addIntermediate(theIncoming.first);
  step->addIntermediate(theIncoming.second);

  return theIncoming;

}
