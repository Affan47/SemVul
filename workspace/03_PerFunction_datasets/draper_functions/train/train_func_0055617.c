IsLoopDead(Loop* L,
                              SmallVector<BasicBlock*, 4>& exitingBlocks,
                              SmallVector<BasicBlock*, 4>& exitBlocks,
                              bool &Changed, BasicBlock *Preheader) {
  BasicBlock* exitBlock = exitBlocks[0];


  BasicBlock::iterator BI = exitBlock->begin();
  while (PHINode* P = dyn_cast<PHINode>(BI)) {
    Value* incoming = P->getIncomingValueForBlock(exitingBlocks[0]);


    for (unsigned i = 1; i < exitingBlocks.size(); ++i) {
      if (incoming != P->getIncomingValueForBlock(exitingBlocks[i]))
        return false;
    }

    if (Instruction* I = dyn_cast<Instruction>(incoming))
      if (!L->makeLoopInvariant(I, Changed, Preheader->getTerminator()))
        return false;

    ++BI;
  }


  for (Loop::block_iterator LI = L->block_begin(), LE = L->block_end();
       LI != LE; ++LI) {
    for (BasicBlock::iterator BI = (*LI)->begin(), BE = (*LI)->end();
         BI != BE; ++BI) {
      if (BI->mayHaveSideEffects())
        return false;
    }
  }

  return true;
}
