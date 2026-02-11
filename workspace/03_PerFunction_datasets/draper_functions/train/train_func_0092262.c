isBitOrNoopPointerCastable(Type *SrcTy, Type *DestTy,
                                          const DataLayout &DL) {
  if (auto *PtrTy = dyn_cast<PointerType>(SrcTy))
    if (auto *IntTy = dyn_cast<IntegerType>(DestTy))
      return IntTy->getBitWidth() == DL.getPointerTypeSizeInBits(PtrTy);
  if (auto *PtrTy = dyn_cast<PointerType>(DestTy))
    if (auto *IntTy = dyn_cast<IntegerType>(SrcTy))
      return IntTy->getBitWidth() == DL.getPointerTypeSizeInBits(PtrTy);

  return isBitCastable(SrcTy, DestTy);
}
