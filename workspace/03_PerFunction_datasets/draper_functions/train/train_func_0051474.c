getLoopID() const {
  MDNode *LoopID = nullptr;
  if (isLoopSimplifyForm()) {
    LoopID = getLoopLatch()->getTerminator()->getMetadata(LoopMDName);
  } else {


    BasicBlock *H = getHeader();
    for (block_iterator I = block_begin(), IE = block_end(); I != IE; ++I) {
      TerminatorInst *TI = (*I)->getTerminator();
      MDNode *MD = nullptr;


      for (unsigned i = 0, ie = TI->getNumSuccessors(); i != ie; ++i) {
        if (TI->getSuccessor(i) == H) {
          MD = TI->getMetadata(LoopMDName);
          break;
        }
      }
      if (!MD)
        return nullptr;

      if (!LoopID)
        LoopID = MD;
      else if (MD != LoopID)
        return nullptr;
    }
  }
  if (!LoopID || LoopID->getNumOperands() == 0 ||
      LoopID->getOperand(0) != LoopID)
    return nullptr;
  return LoopID;
}
