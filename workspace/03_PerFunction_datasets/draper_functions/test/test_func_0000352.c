GetFirstDebugLocInBasicBlock(const BasicBlock *BB) {
  if (const Instruction *I = BB->getFirstNonPHI())
    return I->getDebugLoc();


  return DebugLoc();
}
