isChainSelectCmpBranch(const SelectInst *SI) {
  const BasicBlock *BB = SI->getParent();
  if (!BB)
    return false;
  auto *BI = dyn_cast_or_null<BranchInst>(BB->getTerminator());
  if (!BI || BI->getNumSuccessors() != 2)
    return false;
  auto *IC = dyn_cast<ICmpInst>(BI->getCondition());
  if (!IC || (IC->getOperand(0) != SI && IC->getOperand(1) != SI))
    return false;
  return true;
}
