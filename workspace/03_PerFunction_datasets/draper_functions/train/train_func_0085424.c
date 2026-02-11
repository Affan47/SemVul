getEquivalentLoadRegType(LLVMContext &Ctx, EVT VT) {
  unsigned StoreSize = VT.getStoreSizeInBits();
  if (StoreSize <= 32)
    return EVT::getIntegerVT(Ctx, 32);

  return EVT::getVectorVT(Ctx, MVT::i32, StoreSize / 32);
}
