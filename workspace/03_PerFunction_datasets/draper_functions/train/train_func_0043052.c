getNewAlignment(const SCEV *AASCEV, const SCEV *AlignSCEV,
                                const SCEV *OffSCEV, Value *Ptr,
                                ScalarEvolution *SE) {
  const SCEV *PtrSCEV = SE->getSCEV(Ptr);
  const SCEV *DiffSCEV = SE->getMinusSCEV(PtrSCEV, AASCEV);


  DiffSCEV = SE->getNoopOrSignExtend(DiffSCEV, OffSCEV->getType());


  DiffSCEV = SE->getMinusSCEV(DiffSCEV, OffSCEV);

  DEBUG(dbgs() << "AFI: alignment of " << *Ptr << " relative to " <<
                  *AlignSCEV << " and offset " << *OffSCEV <<
                  " using diff " << *DiffSCEV << "\n");

  unsigned NewAlignment = getNewAlignmentDiff(DiffSCEV, AlignSCEV, SE);
  DEBUG(dbgs() << "\tnew alignment: " << NewAlignment << "\n");

  if (NewAlignment) {
    return NewAlignment;
  } else if (const SCEVAddRecExpr *DiffARSCEV =
             dyn_cast<SCEVAddRecExpr>(DiffSCEV)) {


    const SCEV *DiffStartSCEV = DiffARSCEV->getStart();
    const SCEV *DiffIncSCEV = DiffARSCEV->getStepRecurrence(*SE);

    DEBUG(dbgs() << "\ttrying start/inc alignment using start " <<
                    *DiffStartSCEV << " and inc " << *DiffIncSCEV << "\n");


    NewAlignment = getNewAlignmentDiff(DiffStartSCEV, AlignSCEV, SE);
    unsigned NewIncAlignment = getNewAlignmentDiff(DiffIncSCEV, AlignSCEV, SE);

    DEBUG(dbgs() << "\tnew start alignment: " << NewAlignment << "\n");
    DEBUG(dbgs() << "\tnew inc alignment: " << NewIncAlignment << "\n");

    if (!NewAlignment || !NewIncAlignment) {
      return 0;
    } else if (NewAlignment > NewIncAlignment) {
      if (NewAlignment % NewIncAlignment == 0) {
        DEBUG(dbgs() << "\tnew start/inc alignment: " <<
                        NewIncAlignment << "\n");
        return NewIncAlignment;
      }
    } else if (NewIncAlignment > NewAlignment) {
      if (NewIncAlignment % NewAlignment == 0) {
        DEBUG(dbgs() << "\tnew start/inc alignment: " <<
                        NewAlignment << "\n");
        return NewAlignment;
      }
    } else if (NewIncAlignment == NewAlignment) {
      DEBUG(dbgs() << "\tnew start/inc alignment: " <<
                      NewAlignment << "\n");
      return NewAlignment;
    }
  }

  return 0;
}
