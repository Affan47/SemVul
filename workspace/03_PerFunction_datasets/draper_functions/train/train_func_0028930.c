createPass(AnalysisID ID) {
  const PassInfo *PI = PassRegistry::getPassRegistry()->getPassInfo(ID);
  if (!PI)
    return nullptr;
  return PI->createPass();
}
