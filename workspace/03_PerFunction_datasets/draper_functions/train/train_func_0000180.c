runOnBasicBlock(BasicBlock &BB) {
  if (skipOptnoneFunction(BB))
    return false;

  AA = &getAnalysis<AAResultsWrapperPass>().getAAResults();

  IRBuilder<true, TargetFolder> TheBuilder(
      BB.getContext(), TargetFolder(BB.getModule()->getDataLayout()));
  Builder = &TheBuilder;

  DenseMap<const Value *, SmallVector<LoadPOPPair, 8>> LoadMap;
  AliasSetTracker AST(*AA);

  bool Combined = false;
  unsigned Index = 0;
  for (auto &I : BB) {
    if (I.mayThrow() || (I.mayWriteToMemory() && AST.containsUnknown(&I))) {
      if (combineLoads(LoadMap))
        Combined = true;
      LoadMap.clear();
      AST.clear();
      continue;
    }
    LoadInst *LI = dyn_cast<LoadInst>(&I);
    if (!LI)
      continue;
    ++NumLoadsAnalyzed;
    if (!LI->isSimple() || !LI->getType()->isIntegerTy())
      continue;
    auto POP = getPointerOffsetPair(*LI);
    if (!POP.Pointer)
      continue;
    LoadMap[POP.Pointer].push_back(LoadPOPPair(LI, POP, Index++));
    AST.add(LI);
  }
  if (combineLoads(LoadMap))
    Combined = true;
  return Combined;
}
