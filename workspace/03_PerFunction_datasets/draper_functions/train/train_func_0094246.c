findInductionAndReductions(
    Loop *L, SmallVector<PHINode *, 8> &Inductions,
    SmallVector<PHINode *, 8> &Reductions) {
  if (!L->getLoopLatch() || !L->getLoopPredecessor())
    return false;
  for (BasicBlock::iterator I = L->getHeader()->begin(); isa<PHINode>(I); ++I) {
    RecurrenceDescriptor RD;
    InductionDescriptor ID;
    PHINode *PHI = cast<PHINode>(I);
    if (InductionDescriptor::isInductionPHI(PHI, SE, ID))
      Inductions.push_back(PHI);
    else if (RecurrenceDescriptor::isReductionPHI(PHI, L, RD))
      Reductions.push_back(PHI);
    else {
      DEBUG(
          dbgs() << "Failed to recognize PHI as an induction or reduction.\n");
      return false;
    }
  }
  return true;
}
