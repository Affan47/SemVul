classifyArgument(Value* arg) {

    Type *T = arg->getType();
    if (T->isFPOrFPVectorTy() || T->isX86_MMXTy())
      return AK_FloatingPoint;
    if (T->isIntegerTy() && T->getPrimitiveSizeInBits() <= 64)
      return AK_GeneralPurpose;
    if (T->isPointerTy())
      return AK_GeneralPurpose;
    return AK_Memory;
  }
