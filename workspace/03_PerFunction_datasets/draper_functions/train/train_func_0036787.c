runOnFunction(Function &F) {
  RI = &getAnalysis<RegionInfo>();
  bool Changed = false;


  populateInheritedAnalysis(TPM->activeStack);

  addRegionIntoQueue(RI->getTopLevelRegion(), RQ);

  if (RQ.empty())
    return false;


  for (std::deque<Region *>::const_iterator I = RQ.begin(), E = RQ.end();
       I != E; ++I) {
    Region *R = *I;
    for (unsigned Index = 0; Index < getNumContainedPasses(); ++Index) {
      RegionPass *RP = (RegionPass *)getContainedPass(Index);
      Changed |= RP->doInitialization(R, *this);
    }
  }


  while (!RQ.empty()) {

    CurrentRegion  = RQ.back();
    skipThisRegion = false;
    redoThisRegion = false;


    for (unsigned Index = 0; Index < getNumContainedPasses(); ++Index) {
      RegionPass *P = (RegionPass*)getContainedPass(Index);

      dumpPassInfo(P, EXECUTION_MSG, ON_REGION_MSG,
                   CurrentRegion->getNameStr());
      dumpRequiredSet(P);

      initializeAnalysisImpl(P);

      {
        PassManagerPrettyStackEntry X(P, *CurrentRegion->getEntry());

        TimeRegion PassTimer(getPassTimer(P));
        Changed |= P->runOnRegion(CurrentRegion, *this);
      }

      if (Changed)
        dumpPassInfo(P, MODIFICATION_MSG, ON_REGION_MSG,
                     skipThisRegion ? "<deleted>" :
                                    CurrentRegion->getNameStr());
      dumpPreservedSet(P);

      if (!skipThisRegion) {


        {
          TimeRegion PassTimer(getPassTimer(P));
          CurrentRegion->verifyRegion();
        }


        verifyPreservedAnalysis(P);
      }

      removeNotPreservedAnalysis(P);
      recordAvailableAnalysis(P);
      removeDeadPasses(P,
                       skipThisRegion ? "<deleted>" :
                                      CurrentRegion->getNameStr(),
                       ON_REGION_MSG);

      if (skipThisRegion)

        break;
    }


    if (skipThisRegion)
      for (unsigned Index = 0; Index < getNumContainedPasses(); ++Index) {
        Pass *P = getContainedPass(Index);
        freePass(P, "<deleted>", ON_REGION_MSG);
      }


    RQ.pop_back();

    if (redoThisRegion)
      RQ.push_back(CurrentRegion);


    RI->clearNodeCache();
  }


  for (unsigned Index = 0; Index < getNumContainedPasses(); ++Index) {
    RegionPass *P = (RegionPass*)getContainedPass(Index);
    Changed |= P->doFinalization();
  }


  DEBUG(
    dbgs() << "\nRegion tree of function " << F.getName()
           << " after all region Pass:\n";
    RI->dump();
    dbgs() << "\n";
    );

  return Changed;
}
