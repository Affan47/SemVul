ChkMemSDNodeAddressSpace(SDNode *N,
                                                 unsigned int spN) const {
  const Value *Src = nullptr;
  if (MemSDNode *mN = dyn_cast<MemSDNode>(N)) {
    if (spN == 0 && mN->getMemOperand()->getPseudoValue())
      return true;
    Src = mN->getMemOperand()->getValue();
  }
  if (!Src)
    return false;
  if (auto *PT = dyn_cast<PointerType>(Src->getType()))
    return (PT->getAddressSpace() == spN);
  return false;
}
