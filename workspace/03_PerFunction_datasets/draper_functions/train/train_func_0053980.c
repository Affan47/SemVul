performPromotion(Function &F) {
  std::vector<AllocaInst*> Allocas;
  const DataLayout &DL = F.getParent()->getDataLayout();
  DominatorTree *DT = nullptr;
  if (HasDomTree)
    DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();
  AssumptionCache &AC =
      getAnalysis<AssumptionCacheTracker>().getAssumptionCache(F);

  BasicBlock &BB = F.getEntryBlock();
  DIBuilder DIB(*F.getParent(),  false);
  bool Changed = false;
  SmallVector<Instruction*, 64> Insts;
  while (1) {
    Allocas.clear();


    for (BasicBlock::iterator I = BB.begin(), E = --BB.end(); I != E; ++I)
      if (AllocaInst *AI = dyn_cast<AllocaInst>(I))
        if (tryToMakeAllocaBePromotable(AI, DL))
          Allocas.push_back(AI);

    if (Allocas.empty()) break;

    if (HasDomTree)
      PromoteMemToReg(Allocas, *DT, nullptr, &AC);
    else {
      SSAUpdater SSA;
      for (unsigned i = 0, e = Allocas.size(); i != e; ++i) {
        AllocaInst *AI = Allocas[i];


        for (User *U : AI->users())
          Insts.push_back(cast<Instruction>(U));
        AllocaPromoter(Insts, SSA, &DIB).run(AI, Insts);
        Insts.clear();
      }
    }
    NumPromoted += Allocas.size();
    Changed = true;
  }

  return Changed;
}
