runOnLoop(Loop *L, LPPassManager &) {
    Out << Banner;
    for (Loop::block_iterator b = L->block_begin(), be = L->block_end();
         b != be;
         ++b) {
      (*b)->print(Out);
    }
    return false;
  }
