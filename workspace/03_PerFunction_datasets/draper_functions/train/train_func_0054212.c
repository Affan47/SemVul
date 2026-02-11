isUsedOutsideOfBlock(const BasicBlock *BB) const {
  for (const_use_iterator UI = use_begin(), E = use_end(); UI != E; ++UI) {


    const User *U = *UI;
    const PHINode *PN = dyn_cast<PHINode>(U);
    if (PN == 0) {
      if (cast<Instruction>(U)->getParent() != BB)
        return true;
      continue;
    }

    if (PN->getIncomingBlock(UI) != BB)
      return true;
  }
  return false;
}
