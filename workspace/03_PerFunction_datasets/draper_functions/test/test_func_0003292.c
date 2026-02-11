readInstruction32(ArrayRef<uint8_t> Bytes, uint64_t Address,
                                      uint64_t &Size, uint32_t &Insn,
                                      bool IsBigEndian, bool IsMicroMips) {

  if (Bytes.size() < 4) {
    Size = 0;
    return MCDisassembler::Fail;
  }


  if (IsBigEndian) {

    Insn =
        (Bytes[3] << 0) | (Bytes[2] << 8) | (Bytes[1] << 16) | (Bytes[0] << 24);
  } else {
    if (IsMicroMips) {
      Insn = (Bytes[2] << 0) | (Bytes[3] << 8) | (Bytes[0] << 16) |
             (Bytes[1] << 24);
    } else {
      Insn = (Bytes[0] << 0) | (Bytes[1] << 8) | (Bytes[2] << 16) |
             (Bytes[3] << 24);
    }
  }

  return MCDisassembler::Success;
}
