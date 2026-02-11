getFunctionForValue(Value *V) {
  if (!V) return NULL;
  if (Instruction *I = dyn_cast<Instruction>(V)) {
    BasicBlock *BB = I->getParent();
    return BB ? BB->getParent() : 0;
  }
  if (Argument *A = dyn_cast<Argument>(V))
    return A->getParent();
  if (BasicBlock *BB = dyn_cast<BasicBlock>(V))
    return BB->getParent();
  if (MDNode *MD = dyn_cast<MDNode>(V))
    return MD->getFunction();
  return NULL;
}
