DecodeMem(MCInst &Inst,
                              unsigned Insn,
                              uint64_t Address,
                              const void *Decoder) {
  int Offset = SignExtend32<16>(Insn & 0xffff);
  unsigned Reg = fieldFromInstruction(Insn, 16, 5);
  unsigned Base = fieldFromInstruction(Insn, 21, 5);

  Reg = getReg(Decoder, Mips::GPR32RegClassID, Reg);
  Base = getReg(Decoder, Mips::GPR32RegClassID, Base);

  if (Inst.getOpcode() == Mips::SC ||
      Inst.getOpcode() == Mips::SCD)
    Inst.addOperand(MCOperand::createReg(Reg));

  Inst.addOperand(MCOperand::createReg(Reg));
  Inst.addOperand(MCOperand::createReg(Base));
  Inst.addOperand(MCOperand::createImm(Offset));

  return MCDisassembler::Success;
}
