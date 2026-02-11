isValidOperands(const Value *V1, const Value *V2,
                                        const Value *Mask) {
  if (!V1->getType()->isVectorTy() || V1->getType() != V2->getType())
    return false;

  VectorType *MaskTy = dyn_cast<VectorType>(Mask->getType());
  if (MaskTy == 0 || !MaskTy->getElementType()->isIntegerTy(32))
    return false;


  if (const ConstantVector *MV = dyn_cast<ConstantVector>(Mask)) {
    VectorType *VTy = cast<VectorType>(V1->getType());
    for (unsigned i = 0, e = MV->getNumOperands(); i != e; ++i) {
      if (ConstantInt* CI = dyn_cast<ConstantInt>(MV->getOperand(i))) {
        if (CI->uge(VTy->getNumElements()*2))
          return false;
      } else if (!isa<UndefValue>(MV->getOperand(i))) {
        return false;
      }
    }
  }
  else if (!isa<UndefValue>(Mask) && !isa<ConstantAggregateZero>(Mask))
    return false;

  return true;
}
