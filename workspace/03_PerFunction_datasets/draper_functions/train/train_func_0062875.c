IsNullTerminatedString(const Constant *C) {
  const ArrayType *ATy = cast<ArrayType>(C->getType());


  if (const ConstantArray *CVA = dyn_cast<ConstantArray>(C)) {
    if (ATy->getNumElements() == 0) return false;

    ConstantInt *Null =
      dyn_cast<ConstantInt>(CVA->getOperand(ATy->getNumElements()-1));
    if (Null == 0 || !Null->isZero())
      return false;


    for (unsigned i = 0, e = ATy->getNumElements()-1; i != e; ++i)

      if (!isa<ConstantInt>(CVA->getOperand(i)) ||
          CVA->getOperand(i) == Null)
        return false;
    return true;
  }


  if (isa<ConstantAggregateZero>(C))
    return ATy->getNumElements() == 1;

  return false;
}
