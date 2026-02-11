collectPossibleReductions(Loop *L,
  ReductionTracker &Reductions) {
  BasicBlock *Header = L->getHeader();
  for (BasicBlock::iterator I = Header->begin(),
       IE = Header->getFirstInsertionPt(); I != IE; ++I) {
    if (!isa<PHINode>(I))
      continue;
    if (!I->getType()->isSingleValueType())
      continue;

    SimpleLoopReduction SLR(&*I, L);
    if (!SLR.valid())
      continue;

    DEBUG(dbgs() << "LRR: Possible reduction: " << *I << " (with " <<
          SLR.size() << " chained instructions)\n");
    Reductions.addSLR(SLR);
  }
}
