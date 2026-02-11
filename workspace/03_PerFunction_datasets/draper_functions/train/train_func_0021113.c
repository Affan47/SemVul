runOnFunction(Function &F) {
  LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
  SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();

  bool MadeChange = false;

  for (auto I = LI->begin(), IE = LI->end(); I != IE; ++I)
    for (auto L = df_begin(*I), LE = df_end(*I); L != LE; ++L)
      MadeChange |= runOnLoop(*L);

  return MadeChange;
}
