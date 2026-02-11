getInvariantGroupPointerDependency(LoadInst *LI,
                                                             BasicBlock *BB) {
  Value *LoadOperand = LI->getPointerOperand();


  if (isa<GlobalValue>(LoadOperand))
    return MemDepResult::getUnknown();

  auto *InvariantGroupMD = LI->getMetadata(LLVMContext::MD_invariant_group);
  if (!InvariantGroupMD)
    return MemDepResult::getUnknown();

  MemDepResult Result = MemDepResult::getUnknown();
  llvm::SmallSet<Value *, 14> Seen;

  llvm::SmallVector<Value *, 8> LoadOperandsQueue;
  LoadOperandsQueue.push_back(LoadOperand);
  while (!LoadOperandsQueue.empty()) {
    Value *Ptr = LoadOperandsQueue.pop_back_val();
    if (isa<GlobalValue>(Ptr))
      continue;

    if (auto *BCI = dyn_cast<BitCastInst>(Ptr)) {
      if (!Seen.count(BCI->getOperand(0))) {
        LoadOperandsQueue.push_back(BCI->getOperand(0));
        Seen.insert(BCI->getOperand(0));
      }
    }

    for (Use &Us : Ptr->uses()) {
      auto *U = dyn_cast<Instruction>(Us.getUser());
      if (!U || U == LI || !DT->dominates(U, LI))
        continue;

      if (auto *BCI = dyn_cast<BitCastInst>(U)) {
        if (!Seen.count(BCI)) {
          LoadOperandsQueue.push_back(BCI);
          Seen.insert(BCI);
        }
        continue;
      }


      if ((isa<LoadInst>(U) || isa<StoreInst>(U)) && U->getParent() == BB &&
          U->getMetadata(LLVMContext::MD_invariant_group) == InvariantGroupMD)
        return MemDepResult::getDef(U);
    }
  }
  return Result;
}
