HoistInsertPosition(BasicBlock::iterator IP,
                                 const SmallVectorImpl<Instruction *> &Inputs)
                                                                         const {
  for (;;) {
    const Loop *IPLoop = LI.getLoopFor(IP->getParent());
    unsigned IPLoopDepth = IPLoop ? IPLoop->getLoopDepth() : 0;

    BasicBlock *IDom;
    for (DomTreeNode *Rung = DT.getNode(IP->getParent()); ; ) {
      if (!Rung) return IP;
      Rung = Rung->getIDom();
      if (!Rung) return IP;
      IDom = Rung->getBlock();


      const Loop *IDomLoop = LI.getLoopFor(IDom);
      unsigned IDomDepth = IDomLoop ? IDomLoop->getLoopDepth() : 0;
      if (IDomDepth <= IPLoopDepth &&
          (IDomDepth != IPLoopDepth || IDomLoop == IPLoop))
        break;
    }

    bool AllDominate = true;
    Instruction *BetterPos = 0;
    Instruction *Tentative = IDom->getTerminator();
    for (SmallVectorImpl<Instruction *>::const_iterator I = Inputs.begin(),
         E = Inputs.end(); I != E; ++I) {
      Instruction *Inst = *I;
      if (Inst == Tentative || !DT.dominates(Inst, Tentative)) {
        AllDominate = false;
        break;
      }


      if (IDom == Inst->getParent() &&
          (!BetterPos || DT.dominates(BetterPos, Inst)))
        BetterPos = llvm::next(BasicBlock::iterator(Inst));
    }
    if (!AllDominate)
      break;
    if (BetterPos)
      IP = BetterPos;
    else
      IP = Tentative;
  }

  return IP;
}
