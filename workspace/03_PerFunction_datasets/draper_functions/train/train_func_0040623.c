DecodeT2MOVTWInstruction(MCInst &Inst, unsigned Insn,
                                 uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Rd = fieldFromInstruction(Insn, 8, 4);
  unsigned imm = 0;

  imm |= (fieldFromInstruction(Insn, 0, 8) << 0);
  imm |= (fieldFromInstruction(Insn, 12, 3) << 8);
  imm |= (fieldFromInstruction(Insn, 16, 4) << 12);
  imm |= (fieldFromInstruction(Insn, 26, 1) << 11);

  if (Inst.getOpcode() == ARM::t2MOVTi16)
    if (!Check(S, DecoderGPRRegisterClass(Inst, Rd, Address, Decoder)))
      return MCDisassembler::Fail;
  if (!Check(S, DecoderGPRRegisterClass(Inst, Rd, Address, Decoder)))
    return MCDisassembler::Fail;

  if (!tryAddingSymbolicOperand(Address, imm, false, 4, Inst, Decoder))
    Inst.addOperand(MCOperand::createImm(imm));

  return S;
}
