runOnFunction(Function& F) {
  if (skipOptnoneFunction(F))
    return false;

  if (!NoLoads)
    MD = &getAnalysis<MemoryDependenceAnalysis>();
  DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();
  AC = &getAnalysis<AssumptionCacheTracker>().getAssumptionCache(F);
  TLI = &getAnalysis<TargetLibraryInfoWrapperPass>().getTLI();
  VN.setAliasAnalysis(&getAnalysis<AAResultsWrapperPass>().getAAResults());
  VN.setMemDep(MD);
  VN.setDomTree(DT);

  bool Changed = false;
  bool ShouldContinue = true;


  for (Function::iterator FI = F.begin(), FE = F.end(); FI != FE; ) {
    BasicBlock *BB = &*FI++;

    bool removedBlock =
        MergeBlockIntoPredecessor(BB, DT,  nullptr, MD);
    if (removedBlock) ++NumGVNBlocks;

    Changed |= removedBlock;
  }

  unsigned Iteration = 0;
  while (ShouldContinue) {
    DEBUG(dbgs() << "GVN iteration: " << Iteration << "\n");
    ShouldContinue = iterateOnFunction(F);
    Changed |= ShouldContinue;
    ++Iteration;
  }

  if (EnablePRE) {


    assignValNumForDeadCode();
    bool PREChanged = true;
    while (PREChanged) {
      PREChanged = performPRE(F);
      Changed |= PREChanged;
    }
  }


  cleanupGlobalSets();


  DeadBlocks.clear();

  return Changed;
}
