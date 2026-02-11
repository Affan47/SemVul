DecodeBitpOperand(MCInst &Inst, unsigned Val,
                                      uint64_t Address, const void *Decoder) {
  if (Val > 11)
    return MCDisassembler::Fail;
  static const unsigned Values[] = {
    32 , 1, 2, 3, 4, 5, 6, 7, 8, 16, 24, 32
  };
  Inst.addOperand(MCOperand::createImm(Values[Val]));
  return MCDisassembler::Success;
}
