isAligned(const Value *Base, unsigned Align, const DataLayout &DL) {
  APInt Offset(DL.getTypeStoreSizeInBits(Base->getType()), 0);
  return isAligned(Base, Offset, Align, DL);
}
