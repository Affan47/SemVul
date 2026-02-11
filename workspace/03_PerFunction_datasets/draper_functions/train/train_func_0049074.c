isUseFullyOutsideLoop(const Loop *L) const {

  if (const PHINode *PN = dyn_cast<PHINode>(UserInst)) {
    for (unsigned i = 0, e = PN->getNumIncomingValues(); i != e; ++i)
      if (PN->getIncomingValue(i) == OperandValToReplace &&
          L->contains(PN->getIncomingBlock(i)))
        return false;
    return true;
  }

  return !L->contains(UserInst);
}
