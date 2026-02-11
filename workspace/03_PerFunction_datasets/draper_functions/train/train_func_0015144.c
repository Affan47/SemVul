getMaxValue(const MachineInstr *MI) const {
  const uint64_t F = MI->getDesc().TSFlags;
  unsigned isSigned = (F >> HexagonII::ExtentSignedPos)
                    & HexagonII::ExtentSignedMask;
  unsigned bits =  (F >> HexagonII::ExtentBitsPos)
                    & HexagonII::ExtentBitsMask;

  if (isSigned)
    return ~(-1U << (bits - 1));
  else
    return ~(-1U << bits);
}
