AnalyzeLoadFromClobberingStore(Type *LoadTy, Value *LoadPtr,
                                          StoreInst *DepSI) {

  if (DepSI->getValueOperand()->getType()->isStructTy() ||
      DepSI->getValueOperand()->getType()->isArrayTy())
    return -1;

  const DataLayout &DL = DepSI->getModule()->getDataLayout();
  Value *StorePtr = DepSI->getPointerOperand();
  uint64_t StoreSize =DL.getTypeSizeInBits(DepSI->getValueOperand()->getType());
  return AnalyzeLoadFromClobberingWrite(LoadTy, LoadPtr,
                                        StorePtr, StoreSize, DL);
}
