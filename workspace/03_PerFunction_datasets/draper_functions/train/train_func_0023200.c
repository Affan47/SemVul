InstCombineLoadCast(InstCombiner &IC, LoadInst &LI,
                                        const TargetData *TD) {
  User *CI = cast<User>(LI.getOperand(0));
  Value *CastOp = CI->getOperand(0);

  PointerType *DestTy = cast<PointerType>(CI->getType());
  Type *DestPTy = DestTy->getElementType();
  if (PointerType *SrcTy = dyn_cast<PointerType>(CastOp->getType())) {


    if (DestTy->getAddressSpace() != SrcTy->getAddressSpace())
      return 0;

    Type *SrcPTy = SrcTy->getElementType();

    if (DestPTy->isIntegerTy() || DestPTy->isPointerTy() ||
         DestPTy->isVectorTy()) {


      if (ArrayType *ASrcTy = dyn_cast<ArrayType>(SrcPTy))
        if (Constant *CSrc = dyn_cast<Constant>(CastOp))
          if (ASrcTy->getNumElements() != 0) {
            Value *Idxs[2];
            Idxs[0] = Constant::getNullValue(Type::getInt32Ty(LI.getContext()));
            Idxs[1] = Idxs[0];
            CastOp = ConstantExpr::getGetElementPtr(CSrc, Idxs);
            SrcTy = cast<PointerType>(CastOp->getType());
            SrcPTy = SrcTy->getElementType();
          }

      if (IC.getTargetData() &&
          (SrcPTy->isIntegerTy() || SrcPTy->isPointerTy() ||
            SrcPTy->isVectorTy()) &&


          (SrcPTy->isPointerTy() == LI.getType()->isPointerTy()) &&
          IC.getTargetData()->getTypeSizeInBits(SrcPTy) ==
               IC.getTargetData()->getTypeSizeInBits(DestPTy)) {


        LoadInst *NewLoad =
          IC.Builder->CreateLoad(CastOp, LI.isVolatile(), CI->getName());
        NewLoad->setAlignment(LI.getAlignment());
        NewLoad->setAtomic(LI.getOrdering(), LI.getSynchScope());

        return new BitCastInst(NewLoad, LI.getType());
      }
    }
  }
  return 0;
}
