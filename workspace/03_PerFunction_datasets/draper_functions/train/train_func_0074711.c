isMemThumbRIs4() const {
    if (!isMemory() || Memory.OffsetRegNum != 0 ||
        !isARMLowRegister(Memory.BaseRegNum) || Memory.Alignment != 0)
      return false;

    if (!Memory.OffsetImm) return true;
    int64_t Val = Memory.OffsetImm->getValue();
    return Val >= 0 && Val <= 124 && (Val % 4) == 0;
  }
