isUsedOutsideOfBlock(const BasicBlock *BB) const {
  for (const Use &U : uses()) {


    const Instruction *I = cast<Instruction>(U.getUser());
    const PHINode *PN = dyn_cast<PHINode>(I);
    if (!PN) {
      if (I->getParent() != BB)
        return true;
      continue;
    }

    if (PN->getIncomingBlock(U) != BB)
      return true;
  }
  return false;
}
