runOnFunction(Function &F) {

  if (!F.hasGC())
    return false;

  GCFunctionInfo &FI = getAnalysis<GCModuleInfo>().getFunctionInfo(F);
  GCStrategy &S = FI.getStrategy();

  bool MadeChange = false;

  if (NeedsDefaultLoweringPass(S))
    MadeChange |= PerformDefaultLowering(F, S);

  return MadeChange;
}
