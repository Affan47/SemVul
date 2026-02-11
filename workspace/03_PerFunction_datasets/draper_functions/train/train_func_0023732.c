dominates(BasicBlock *BB, DominatorTree *DT) const {
  return DT->dominates(L->getHeader(), BB) &&
         SCEVNAryExpr::dominates(BB, DT);
}
