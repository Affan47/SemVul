ValueDominatesPHI(Value *V, PHINode *P, const DominatorTree *DT) {
  Instruction *I = dyn_cast<Instruction>(V);
  if (!I)

    return true;


  if (!I->getParent() || !P->getParent() || !I->getParent()->getParent())
    return false;


  if (DT) {
    if (!DT->isReachableFromEntry(P->getParent()))
      return true;
    if (!DT->isReachableFromEntry(I->getParent()))
      return false;
    return DT->dominates(I, P);
  }


  if (I->getParent() == &I->getParent()->getParent()->getEntryBlock() &&
      !isa<InvokeInst>(I) && !isa<CatchPadInst>(I))
    return true;

  return false;
}
