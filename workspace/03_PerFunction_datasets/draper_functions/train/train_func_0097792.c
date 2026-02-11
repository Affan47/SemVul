getANDriOpcode(bool IsLP64, int64_t Imm) {
  if (IsLP64) {
    if (isInt<8>(Imm))
      return X86::AND64ri8;
    return X86::AND64ri32;
  }
  if (isInt<8>(Imm))
    return X86::AND32ri8;
  return X86::AND32ri;
}
