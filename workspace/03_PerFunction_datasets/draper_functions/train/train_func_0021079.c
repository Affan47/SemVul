getElementValue(Constant *C) const {
  if (isa<SequentialType>(getType()))
    return getSequentialElement();
  return getStructElement(cast<ConstantInt>(C)->getZExtValue());
}
