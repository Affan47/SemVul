MergeIfRegion(BasicBlock *BB, IRBuilder<> &Builder,
                                  Pass *P) {
  BasicBlock *IfTrue2, *IfFalse2;
  Value *IfCond2 = GetIfCondition(BB, IfTrue2, IfFalse2);
  Instruction *CInst2 = dyn_cast_or_null<Instruction>(IfCond2);
  if (!CInst2)
    return false;

  BasicBlock *SecondEntryBlock = CInst2->getParent();
  if (SecondEntryBlock->hasAddressTaken())
    return false;

  BasicBlock *IfTrue1, *IfFalse1;
  Value *IfCond1 = GetIfCondition(SecondEntryBlock, IfTrue1, IfFalse1);
  Instruction *CInst1 = dyn_cast_or_null<Instruction>(IfCond1);
  if (!CInst1)
    return false;

  BasicBlock *FirstEntryBlock = CInst1->getParent();


  if ((IfTrue1 != FirstEntryBlock) && (IfFalse1 != FirstEntryBlock))
    return false;
  if ((IfTrue2 != SecondEntryBlock) && (IfFalse2 != SecondEntryBlock))
    return false;

  TerminatorInst *PTI2 = SecondEntryBlock->getTerminator();
  Instruction *PBI2 = &SecondEntryBlock->front();

  if (!CompareIfRegionBlock(FirstEntryBlock, SecondEntryBlock, IfTrue1,
                            IfTrue2))
    return false;

  if (!CompareIfRegionBlock(FirstEntryBlock, SecondEntryBlock, IfFalse1,
                            IfFalse2))
    return false;


  for (BasicBlock::iterator BI(PBI2), BE(PTI2); BI != BE; ++BI) {
    Instruction *CI = &*BI;
    if (isa<PHINode>(CI) || CI->mayHaveSideEffects() ||
        !isSafeToSpeculativelyExecute(CI))
      return false;
  }


  FirstEntryBlock->getInstList().pop_back();
  FirstEntryBlock->getInstList()
      .splice(FirstEntryBlock->end(), SecondEntryBlock->getInstList());
  BranchInst *PBI = dyn_cast<BranchInst>(FirstEntryBlock->getTerminator());
  Value *CC = PBI->getCondition();
  BasicBlock *SaveInsertBB = Builder.GetInsertBlock();
  BasicBlock::iterator SaveInsertPt = Builder.GetInsertPoint();
  Builder.SetInsertPoint(PBI);
  Value *NC = Builder.CreateOr(CInst1, CC);
  PBI->replaceUsesOfWith(CC, NC);
  Builder.SetInsertPoint(SaveInsertBB, SaveInsertPt);


  if (IfTrue1 != FirstEntryBlock) {
    IfTrue1->dropAllReferences();
    IfTrue1->eraseFromParent();
  }


  if (IfFalse1 != FirstEntryBlock) {
    IfFalse1->dropAllReferences();
    IfFalse1->eraseFromParent();
  }


  SecondEntryBlock->dropAllReferences();
  SecondEntryBlock->eraseFromParent();
  DEBUG(dbgs() << "If conditions merged into:\n" << *FirstEntryBlock);
  return true;
}
