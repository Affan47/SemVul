DecodeIT(MCInst &Inst, unsigned Insn,
                             uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;
  unsigned pred = fieldFromInstruction(Insn, 4, 4);
  unsigned mask = fieldFromInstruction(Insn, 0, 4);

  if (pred == 0xF) {
    pred = 0xE;
    S = MCDisassembler::SoftFail;
  }

  if (mask == 0x0)
    return MCDisassembler::Fail;

  Inst.addOperand(MCOperand::createImm(pred));
  Inst.addOperand(MCOperand::createImm(mask));
  return S;
}
