ExtractLoop(DominatorTree &DT, Loop *L, bool AggregateArgs) {
  return CodeExtractor(&DT, AggregateArgs).ExtractCodeRegion(L->getBlocks());
}
