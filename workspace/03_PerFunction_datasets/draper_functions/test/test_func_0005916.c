GetMemInstValueForLoad(MemIntrinsic *SrcInst, unsigned Offset,
                                     Type *LoadTy, Instruction *InsertPt,
                                     const DataLayout &DL){
  LLVMContext &Ctx = LoadTy->getContext();
  uint64_t LoadSize = DL.getTypeSizeInBits(LoadTy)/8;

  IRBuilder<> Builder(InsertPt);


  if (MemSetInst *MSI = dyn_cast<MemSetInst>(SrcInst)) {


    Value *Val = MSI->getValue();
    if (LoadSize != 1)
      Val = Builder.CreateZExt(Val, IntegerType::get(Ctx, LoadSize*8));

    Value *OneElt = Val;


    for (unsigned NumBytesSet = 1; NumBytesSet != LoadSize; ) {

      if (NumBytesSet*2 <= LoadSize) {
        Value *ShVal = Builder.CreateShl(Val, NumBytesSet*8);
        Val = Builder.CreateOr(Val, ShVal);
        NumBytesSet <<= 1;
        continue;
      }


      Value *ShVal = Builder.CreateShl(Val, 1*8);
      Val = Builder.CreateOr(OneElt, ShVal);
      ++NumBytesSet;
    }

    return CoerceAvailableValueToLoadType(Val, LoadTy, Builder, DL);
  }


  MemTransferInst *MTI = cast<MemTransferInst>(SrcInst);
  Constant *Src = cast<Constant>(MTI->getSource());
  unsigned AS = Src->getType()->getPointerAddressSpace();


  Src = ConstantExpr::getBitCast(Src,
                                 Type::getInt8PtrTy(Src->getContext(), AS));
  Constant *OffsetCst =
    ConstantInt::get(Type::getInt64Ty(Src->getContext()), (unsigned)Offset);
  Src = ConstantExpr::getGetElementPtr(Type::getInt8Ty(Src->getContext()), Src,
                                       OffsetCst);
  Src = ConstantExpr::getBitCast(Src, PointerType::get(LoadTy, AS));
  return ConstantFoldLoadFromConstPtr(Src, DL);
}
