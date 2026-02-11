GetStoreValueForLoad(Value *SrcVal, unsigned Offset,
                                   const Type *LoadTy,
                                   Instruction *InsertPt, const TargetData &TD){
  LLVMContext &Ctx = SrcVal->getType()->getContext();

  uint64_t StoreSize = (TD.getTypeSizeInBits(SrcVal->getType()) + 7) / 8;
  uint64_t LoadSize = (TD.getTypeSizeInBits(LoadTy) + 7) / 8;

  IRBuilder<> Builder(InsertPt->getParent(), InsertPt);


  if (SrcVal->getType()->isPointerTy())
    SrcVal = Builder.CreatePtrToInt(SrcVal, TD.getIntPtrType(Ctx), "tmp");
  if (!SrcVal->getType()->isIntegerTy())
    SrcVal = Builder.CreateBitCast(SrcVal, IntegerType::get(Ctx, StoreSize*8),
                                   "tmp");


  unsigned ShiftAmt;
  if (TD.isLittleEndian())
    ShiftAmt = Offset*8;
  else
    ShiftAmt = (StoreSize-LoadSize-Offset)*8;

  if (ShiftAmt)
    SrcVal = Builder.CreateLShr(SrcVal, ShiftAmt, "tmp");

  if (LoadSize != StoreSize)
    SrcVal = Builder.CreateTrunc(SrcVal, IntegerType::get(Ctx, LoadSize*8),
                                 "tmp");

  return CoerceAvailableValueToLoadType(SrcVal, LoadTy, InsertPt, TD);
}
