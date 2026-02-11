ChangeToUnreachable(Instruction *I, bool UseLLVMTrap) {
  BasicBlock *BB = I->getParent();


  for (succ_iterator SI = succ_begin(BB), SE = succ_end(BB); SI != SE; ++SI)
    (*SI)->removePredecessor(BB);


  if (UseLLVMTrap) {
    Function *TrapFn =
      Intrinsic::getDeclaration(BB->getParent()->getParent(), Intrinsic::trap);
    CallInst::Create(TrapFn, "", I);
  }
  new UnreachableInst(I->getContext(), I);


  BasicBlock::iterator BBI = I, BBE = BB->end();
  while (BBI != BBE) {
    if (!BBI->use_empty())
      BBI->replaceAllUsesWith(UndefValue::get(BBI->getType()));
    BB->getInstList().erase(BBI++);
  }
}
