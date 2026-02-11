getAllocatableClass(const TargetRegisterClass *RC) const {
  if (!RC || RC->isAllocatable())
    return RC;

  const unsigned *SubClass = RC->getSubClassMask();
  for (unsigned Base = 0, BaseE = getNumRegClasses();
       Base < BaseE; Base += 32) {
    unsigned Idx = Base;
    for (unsigned Mask = *SubClass++; Mask; Mask >>= 1) {
      unsigned Offset = countTrailingZeros(Mask);
      const TargetRegisterClass *SubRC = getRegClass(Idx + Offset);
      if (SubRC->isAllocatable())
        return SubRC;
      Mask >>= Offset;
      Idx += Offset + 1;
    }
  }
  return nullptr;
}
