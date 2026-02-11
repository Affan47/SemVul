DecodeT2AddrModeImm0_1020s4(MCInst &Inst,unsigned Val,
                                   uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Rn = fieldFromInstruction(Val, 8, 4);
  unsigned imm = fieldFromInstruction(Val, 0, 8);

  if (!Check(S, DecodeGPRnopcRegisterClass(Inst, Rn, Address, Decoder)))
    return MCDisassembler::Fail;

  Inst.addOperand(MCOperand::createImm(imm));

  return S;
}
