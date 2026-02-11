getUnprocPredCount(BasicBlock *Block) const {
    unsigned Count = 0;
    for (pred_iterator I = pred_begin(Block), E = pred_end(Block); I != E; ++I)
      if (!Blocks.count(*I)) Count++;
    return Count;
  }
