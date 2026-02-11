UpdatePHINodes(BasicBlock *OrigBB, BasicBlock *NewBB,
                           ArrayRef<BasicBlock *> Preds, BranchInst *BI,
                           bool HasLoopExit) {

  SmallPtrSet<BasicBlock *, 16> PredSet(Preds.begin(), Preds.end());
  for (BasicBlock::iterator I = OrigBB->begin(); isa<PHINode>(I); ) {
    PHINode *PN = cast<PHINode>(I++);


    Value *InVal = nullptr;
    if (!HasLoopExit) {
      InVal = PN->getIncomingValueForBlock(Preds[0]);
      for (unsigned i = 0, e = PN->getNumIncomingValues(); i != e; ++i) {
        if (!PredSet.count(PN->getIncomingBlock(i)))
          continue;
        if (!InVal)
          InVal = PN->getIncomingValue(i);
        else if (InVal != PN->getIncomingValue(i)) {
          InVal = nullptr;
          break;
        }
      }
    }

    if (InVal) {


      for (int64_t i = PN->getNumIncomingValues() - 1; i >= 0; --i)
        if (PredSet.count(PN->getIncomingBlock(i)))
          PN->removeIncomingValue(i, false);


      PN->addIncoming(InVal, NewBB);
      continue;
    }


    PHINode *NewPHI =
        PHINode::Create(PN->getType(), Preds.size(), PN->getName() + ".ph", BI);


    for (int64_t i = PN->getNumIncomingValues() - 1; i >= 0; --i) {
      BasicBlock *IncomingBB = PN->getIncomingBlock(i);
      if (PredSet.count(IncomingBB)) {
        Value *V = PN->removeIncomingValue(i, false);
        NewPHI->addIncoming(V, IncomingBB);
      }
    }

    PN->addIncoming(NewPHI, NewBB);
  }
}
