DecodeT2Imm8S4(MCInst &Inst, unsigned Val,
                           uint64_t Address, const void *Decoder) {
  if (Val == 0)
    Inst.addOperand(MCOperand::createImm(INT32_MIN));
  else {
    int imm = Val & 0xFF;

    if (!(Val & 0x100)) imm *= -1;
    Inst.addOperand(MCOperand::createImm(imm * 4));
  }

  return MCDisassembler::Success;
}
