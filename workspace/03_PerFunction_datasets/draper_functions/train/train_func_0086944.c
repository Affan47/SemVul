dominates(const Instruction *A, const Instruction *B) const{
  const BasicBlock *BBA = A->getParent(), *BBB = B->getParent();


  if (const InvokeInst *II = dyn_cast<InvokeInst>(A))
    BBA = II->getNormalDest();

  if (BBA != BBB) return dominates(BBA, BBB);


  if (isa<PHINode>(A) && isa<PHINode>(B))
    return false;


  BasicBlock::const_iterator I = BBA->begin();
  for (; &*I != A && &*I != B; ++I)
    ;

  return &*I == A;
}
