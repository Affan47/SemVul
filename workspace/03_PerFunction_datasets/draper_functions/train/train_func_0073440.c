isDSOffsetLegal(const SDValue &Base, unsigned Offset,
                                         unsigned OffsetBits) const {
  if ((OffsetBits == 16 && !isUInt<16>(Offset)) ||
      (OffsetBits == 8 && !isUInt<8>(Offset)))
    return false;

  if (Subtarget->getGeneration() >= AMDGPUSubtarget::SEA_ISLANDS ||
      Subtarget->unsafeDSOffsetFoldingEnabled())
    return true;


  return CurDAG->SignBitIsZero(Base);
}
