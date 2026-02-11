EmitGEPOffset(User *GEP) {
  TargetData &TD = *getTargetData();
  gep_type_iterator GTI = gep_type_begin(GEP);
  Type *IntPtrTy = TD.getIntPtrType(GEP->getContext());
  Value *Result = Constant::getNullValue(IntPtrTy);


  bool isInBounds = cast<GEPOperator>(GEP)->isInBounds();


  unsigned IntPtrWidth = TD.getPointerSizeInBits();
  uint64_t PtrSizeMask = ~0ULL >> (64-IntPtrWidth);

  for (User::op_iterator i = GEP->op_begin() + 1, e = GEP->op_end(); i != e;
       ++i, ++GTI) {
    Value *Op = *i;
    uint64_t Size = TD.getTypeAllocSize(GTI.getIndexedType()) & PtrSizeMask;
    if (ConstantInt *OpC = dyn_cast<ConstantInt>(Op)) {
      if (OpC->isZero()) continue;


      if (StructType *STy = dyn_cast<StructType>(*GTI)) {
        Size = TD.getStructLayout(STy)->getElementOffset(OpC->getZExtValue());

        if (Size)
          Result = Builder->CreateAdd(Result, ConstantInt::get(IntPtrTy, Size),
                                      GEP->getName()+".offs");
        continue;
      }

      Constant *Scale = ConstantInt::get(IntPtrTy, Size);
      Constant *OC =
              ConstantExpr::getIntegerCast(OpC, IntPtrTy, true );
      Scale = ConstantExpr::getMul(OC, Scale, isInBounds);

      Result = Builder->CreateAdd(Result, Scale, GEP->getName()+".offs");
      continue;
    }

    if (Op->getType() != IntPtrTy)
      Op = Builder->CreateIntCast(Op, IntPtrTy, true, Op->getName()+".c");
    if (Size != 1) {

      Op = Builder->CreateMul(Op, ConstantInt::get(IntPtrTy, Size),
                              GEP->getName()+".idx", isInBounds );
    }


    Result = Builder->CreateAdd(Op, Result, GEP->getName()+".offs");
  }
  return Result;
}
