isMemNegImm8Offset() const {
    if (!isMemory() || Memory.OffsetRegNum != 0 || Memory.Alignment != 0)
      return false;

    if (!Memory.OffsetImm) return true;
    int64_t Val = Memory.OffsetImm->getValue();
    return Val > -256 && Val < 0;
  }
