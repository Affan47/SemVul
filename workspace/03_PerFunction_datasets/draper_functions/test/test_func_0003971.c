expand(const SCEV *S) {


  Instruction *InsertPt = Builder.GetInsertPoint();
  for (Loop *L = SE.LI->getLoopFor(Builder.GetInsertBlock()); ;
       L = L->getParentLoop())
    if (SE.isLoopInvariant(S, L)) {
      if (!L) break;
      if (BasicBlock *Preheader = L->getLoopPreheader())
        InsertPt = Preheader->getTerminator();
    } else {


      if (L && SE.hasComputableLoopEvolution(S, L) && !PostIncLoops.count(L))
        InsertPt = L->getHeader()->getFirstInsertionPt();
      while (isInsertedInstruction(InsertPt) || isa<DbgInfoIntrinsic>(InsertPt))
        InsertPt = llvm::next(BasicBlock::iterator(InsertPt));
      break;
    }


  std::map<std::pair<const SCEV *, Instruction *>,
           AssertingVH<Value> >::iterator I =
    InsertedExpressions.find(std::make_pair(S, InsertPt));
  if (I != InsertedExpressions.end())
    return I->second;

  BasicBlock *SaveInsertBB = Builder.GetInsertBlock();
  BasicBlock::iterator SaveInsertPt = Builder.GetInsertPoint();
  Builder.SetInsertPoint(InsertPt->getParent(), InsertPt);


  Value *V = visit(S);


  InsertedExpressions[std::make_pair(S, InsertPt)] = V;

  restoreInsertPoint(SaveInsertBB, SaveInsertPt);
  return V;
}
