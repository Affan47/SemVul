runOnFunction(Function &F) override {
    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    DA = &getAnalysis<DependenceAnalysis>();
    auto *DTWP = getAnalysisIfAvailable<DominatorTreeWrapperPass>();
    DT = DTWP ? &DTWP->getDomTree() : nullptr;

    SmallVector<LoopVector, 8> Worklist;

    for (Loop *L : *LI)
      populateWorklist(*L, Worklist);

    DEBUG(dbgs() << "Worklist size = " << Worklist.size() << "\n");
    bool Changed = true;
    while (!Worklist.empty()) {
      LoopVector LoopList = Worklist.pop_back_val();
      Changed = processLoopList(LoopList, F);
    }
    return Changed;
  }
