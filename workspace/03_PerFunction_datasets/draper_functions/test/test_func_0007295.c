runOnFunction(Function &F) {
  if (PImpl)
    getCache(PImpl).clear();

  TD = getAnalysisIfAvailable<TargetData>();

  return false;
}
