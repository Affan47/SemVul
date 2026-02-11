runOnLoop(Loop *L, LPPassManager &LPM) {
  if (skipOptnoneFunction(L))
    return false;

  AA = &getAnalysis<AAResultsWrapperPass>().getAAResults();
  LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
  SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
  TLI = &getAnalysis<TargetLibraryInfoWrapperPass>().getTLI();
  DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();

  BasicBlock *Header = L->getHeader();
  DEBUG(dbgs() << "LRR: F[" << Header->getParent()->getName() <<
        "] Loop %" << Header->getName() << " (" <<
        L->getNumBlocks() << " block(s))\n");

  bool Changed = false;


  if (L->getNumBlocks() > 1)
    return Changed;

  if (!SE->hasLoopInvariantBackedgeTakenCount(L))
    return Changed;

  const SCEV *LIBETC = SE->getBackedgeTakenCount(L);
  const SCEV *IterCount = SE->getAddExpr(LIBETC, SE->getOne(LIBETC->getType()));
  DEBUG(dbgs() << "LRR: iteration count = " << *IterCount << "\n");


  SmallInstructionVector PossibleIVs;
  IVToIncMap.clear();
  collectPossibleIVs(L, PossibleIVs);

  if (PossibleIVs.empty()) {
    DEBUG(dbgs() << "LRR: No possible IVs found\n");
    return Changed;
  }

  ReductionTracker Reductions;
  collectPossibleReductions(L, Reductions);


  for (SmallInstructionVector::iterator I = PossibleIVs.begin(),
       IE = PossibleIVs.end(); I != IE; ++I)
    if (reroll(*I, L, Header, IterCount, Reductions)) {
      Changed = true;
      break;
    }

  return Changed;
}
