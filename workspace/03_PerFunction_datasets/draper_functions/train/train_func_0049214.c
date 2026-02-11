insertPHIStore(
    BasicBlock *PredBlock, Value *PredVal, AllocaInst *SpillSlot,
    SmallVectorImpl<std::pair<BasicBlock *, Value *>> &Worklist) {

  if (PredBlock->isEHPad() &&
      !isa<CleanupPadInst>(PredBlock->getFirstNonPHI())) {

    Worklist.push_back({PredBlock, PredVal});
    return;
  }


  new StoreInst(PredVal, SpillSlot, PredBlock->getTerminator());
}
