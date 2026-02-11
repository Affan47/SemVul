hasDedicatedExits() const {


  SmallPtrSet<BasicBlock *, 16> LoopBBs(block_begin(), block_end());


  SmallVector<BasicBlock *, 4> ExitBlocks;
  getExitBlocks(ExitBlocks);
  for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i)
    for (pred_iterator PI = pred_begin(ExitBlocks[i]),
         PE = pred_end(ExitBlocks[i]); PI != PE; ++PI)
      if (!LoopBBs.count(*PI))
        return false;

  return true;
}
