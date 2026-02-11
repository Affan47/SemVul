isString() const {

  if (!getType()->getElementType()->isIntegerTy(8))
    return false;


  for (unsigned i = 0, e = getNumOperands(); i != e; ++i)
    if (!isa<ConstantInt>(getOperand(i)))
      return false;
  return true;
}
