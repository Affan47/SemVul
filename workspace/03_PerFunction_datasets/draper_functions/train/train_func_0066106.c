DecodeTSTInstruction(MCInst &Inst, unsigned Insn,
                                  uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Pred = fieldFromInstruction(Insn, 28, 4);
  unsigned Rn = fieldFromInstruction(Insn, 16, 4);
  unsigned Rm = fieldFromInstruction(Insn, 0, 4);

  if (Pred == 0xF)
    return DecodeSETPANInstruction(Inst, Insn, Address, Decoder);

  if (!Check(S, DecodeGPRRegisterClass(Inst, Rn, Address, Decoder)))
    return MCDisassembler::Fail;
  if (!Check(S, DecodeGPRRegisterClass(Inst, Rm, Address, Decoder)))
    return MCDisassembler::Fail;
  if (!Check(S, DecodePredicateOperand(Inst, Pred, Address, Decoder)))
    return MCDisassembler::Fail;

  return S;
}
