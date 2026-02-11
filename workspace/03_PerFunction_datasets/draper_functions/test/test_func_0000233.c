DecodeSMLAInstruction(MCInst &Inst, unsigned Insn,
                                 uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Rd = fieldFromInstruction(Insn, 16, 4);
  unsigned Rn = fieldFromInstruction(Insn, 0, 4);
  unsigned Rm = fieldFromInstruction(Insn, 8, 4);
  unsigned Ra = fieldFromInstruction(Insn, 12, 4);
  unsigned pred = fieldFromInstruction(Insn, 28, 4);

  if (pred == 0xF)
    return DecodeCPSInstruction(Inst, Insn, Address, Decoder);

  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Rd, Address, Decoder)))
    return MCDisassembler::Fail;
  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Rn, Address, Decoder)))
    return MCDisassembler::Fail;
  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Rm, Address, Decoder)))
    return MCDisassembler::Fail;
  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Ra, Address, Decoder)))
    return MCDisassembler::Fail;

  if (!Check(S, DecodePredicateOperand(Inst, pred, Address, Decoder)))
    return MCDisassembler::Fail;

  return S;
}
