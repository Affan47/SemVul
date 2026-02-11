AnalyzeLoadFromClobberingLoad(Type *LoadTy, Value *LoadPtr,
                                         LoadInst *DepLI, const DataLayout &DL){

  if (DepLI->getType()->isStructTy() || DepLI->getType()->isArrayTy())
    return -1;

  Value *DepPtr = DepLI->getPointerOperand();
  uint64_t DepSize = DL.getTypeSizeInBits(DepLI->getType());
  int R = AnalyzeLoadFromClobberingWrite(LoadTy, LoadPtr, DepPtr, DepSize, DL);
  if (R != -1) return R;


  int64_t LoadOffs = 0;
  const Value *LoadBase =
      GetPointerBaseWithConstantOffset(LoadPtr, LoadOffs, DL);
  unsigned LoadSize = DL.getTypeStoreSize(LoadTy);

  unsigned Size = MemoryDependenceAnalysis::getLoadLoadClobberFullWidthSize(
      LoadBase, LoadOffs, LoadSize, DepLI);
  if (Size == 0) return -1;

  return AnalyzeLoadFromClobberingWrite(LoadTy, LoadPtr, DepPtr, Size*8, DL);
}
