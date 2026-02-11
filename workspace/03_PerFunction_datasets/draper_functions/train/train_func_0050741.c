isCString() const {

  if (!getType()->getElementType()->isIntegerTy(8))
    return false;


  if (!getOperand(getNumOperands()-1)->isNullValue())
    return false;

  for (unsigned i = 0, e = getNumOperands()-1; i != e; ++i) {
    if (!isa<ConstantInt>(getOperand(i)))
      return false;
    if (getOperand(i)->isNullValue())
      return false;
  }
  return true;
}
