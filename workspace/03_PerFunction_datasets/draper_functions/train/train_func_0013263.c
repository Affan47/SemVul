runOnFunction(Function &F) {
  if (skipOptnoneFunction(F))
    return false;

  TTI = &getAnalysis<TargetTransformInfoWrapperPass>().getTTI(F);

  bool Changed = false;
  for (auto& B : F) {
    Changed |= runOnBasicBlock(B);
  }
  return Changed;
}
