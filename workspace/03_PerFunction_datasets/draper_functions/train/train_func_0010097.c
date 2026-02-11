restoreInsertPoint(BasicBlock *BB, BasicBlock::iterator I) {


  while (isInsertedInstruction(I) || isa<DbgInfoIntrinsic>(I)) ++I;

  Builder.SetInsertPoint(BB, I);
}
