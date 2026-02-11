InsertPreheaderForLoop(Loop *L) {
  BasicBlock *Header = L->getHeader();


  SmallVector<BasicBlock*, 8> OutsideBlocks;
  for (pred_iterator PI = pred_begin(Header), PE = pred_end(Header);
       PI != PE; ++PI) {
    BasicBlock *P = *PI;
    if (!L->contains(P)) {


      if (isa<IndirectBrInst>(P->getTerminator())) return 0;


      OutsideBlocks.push_back(P);
    }
  }


  BasicBlock *NewBB =
    SplitBlockPredecessors(Header, &OutsideBlocks[0], OutsideBlocks.size(),
                           ".preheader", this);

  NewBB->getTerminator()->setDebugLoc(Header->getFirstNonPHI()->getDebugLoc());
  DEBUG(dbgs() << "LoopSimplify: Creating pre-header " << NewBB->getName()
               << "\n");


  PlaceSplitBlockCarefully(NewBB, OutsideBlocks, L);

  return NewBB;
}
